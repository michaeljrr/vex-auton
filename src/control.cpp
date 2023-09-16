#include "main.h"
#include "odom.h"
#include "global.hpp"
#include "api.h"

#define DEFAULT_KP 0.17
#define DEFAULT_KI 0
#define DEFAULT_KD 5
#define DEFAULT_TURN_KP 0.29
#define DEFAULT_TURN_KI 0
#define DEFAULT_TURN_KD 10
#define KI_LIMIT 0
#define RAMPING_POW 1
#define DISTANCE_LEEWAY 15
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0;
double errorEncdL = 0, errorEncdR = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD, kI = DEFAULT_KI;

bool turnMode = false, pauseBase = false;

void baseMove(double dis, double kp, double ki, double kd){\
  targEncdL = encdL;
  targEncdR = encdR;
  // resetPrevEncd();
  printf("baseMove(%.2f)\n", dis);
  targEncdL += dis/inPerDeg;
  targEncdR += dis/inPerDeg;

  kP = kp;
  kI = ki;
  kD = kd;
}

void baseMove(double dis){
    baseMove(dis, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}

void baseMove(double x, double y, double p, double i, double d){
  printf("baseMove(%.2f, %.2f)\n", x, y);
	double errY = y-Y;
	double errX = x-X;
	double distance = sqrt(errY*errY + errX*errX);
	double targAngle = atan2(errX,errY);
	// printf("Angle: %f %f", targAngle, position.angle);
	// printf("Distance: %f",distance);

	int negator = 1;
  if(fabs(targAngle-angle) >= pi/2) negator = -1;

  targEncdL += distance/inPerDeg*negator;
  targEncdR += distance/inPerDeg*negator;

  kP = p;
  kI = i;
  kD = d;
}

void baseMove(double x, double y){
  baseMove(x, y, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}


void baseTurn(double a, double kp, double ki, double kd){
  // wait(100, msec);
  printf("baseTurn(%.2f, %.2f, %.2f)\n", a, kp, kd);
  double error = a*toRad - angle;
  double diff = error*baseWidth/inPerDeg/2;

  targEncdL += diff;
  targEncdR += -diff;
	kP = kp;
  kI = ki;
	kD = kd;
}

void baseTurn(double a){
  baseTurn(a, DEFAULT_TURN_KP, DEFAULT_TURN_KI, DEFAULT_TURN_KD);
}

void baseTurnRelative(double a, double p, double i, double d){

  double diff = a*toRad*baseWidth/inPerDeg/2;
  targEncdL += diff;
  targEncdR += -diff;

  kP = p;
  kI = i;
  kD = d;
}

void baseTurnRelative(double a){
  baseTurnRelative(a, DEFAULT_TURN_KP, DEFAULT_TURN_KI, DEFAULT_KD);
}

void baseTurn(double x, double y, double p, double i, double d, bool inverted){
  printf("deltas: %.2f, %.2f\n", x, X);
	double targAngle = atan2((x-X), (y-Y));
  printf("Turn to angle: %.2f\n", targAngle / toRad);
	if(inverted) targAngle -= halfPI;
  // double diff = (targAngle - angle + lastResetAngle)*baseWidth/inPerDeg/2;
  // targEncdL += diff;
  // targEncdR += -diff;
  // kP = p;
  // kD = d;
  double diffAngle = boundRad(targAngle-angle);
  if(diffAngle > PI) diffAngle -= twoPI;
  targAngle = angle + diffAngle;
  printf("diffANgle: %.1f\n", diffAngle*toDeg);
  baseTurn(targAngle*toDeg, p, i, d);
}

void baseTurn(double x, double y, bool inverted){
  baseTurn(x,y,DEFAULT_TURN_KP,DEFAULT_TURN_KI,DEFAULT_TURN_KD,inverted);
}

void powerBase(double l, double r) {
  printf("powerBase(%.2f, %.2f)\n", l, r);
  pauseBase = true;
  powerL = l;
  powerR = r;
}

void timerBase(double l, double r, double t) {
  printf("timerBase(%.2f, %.2f, %.2f)\n", l, r, t);
  pauseBase = true;
  powerL = l;
  powerR = r;
  pros::delay(t);
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y, angle);
}

void unPauseBase() {
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y, angle);
}

void waitBase(double cutoff){
  pros::delay(cutoff);
  // targEncdL = encdL;
  // targEncdR = encdR;
  resetPrevEncd();
}

void waitBaseNoD(double cutoff){
	//double start = Timer.time();
  //while((fabs(targEncdL - encdL) > DISTANCE_LEEWAY || fabs(targEncdR - encdR) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) 
  pros::delay(20);
  //printf("Time taken %.2f\n", (Timer.time() - start));
  // wait(200, msec);
  // targEncdL = encdL;
  // targEncdR = encdR;
  resetPrevEncd();
}

int Control(){
	pros::Motor lf_wheel (lf_port);
  pros::Motor rf_wheel (rf_port);
  int dT = 5;
  double prevErrorEncdL = 0, prevErrorEncdR = 0, integralL = 0, integralR = 0;
  while(true){
    if(!pauseBase) {
      errorEncdL = targEncdL - encdL;
      errorEncdR = targEncdR - encdR;

      if(fabs(errorEncdL) < KI_LIMIT) integralL += errorEncdL;
      else integralL = 0;
      if(fabs(errorEncdR) < KI_LIMIT) integralR += errorEncdR;
      else integralR = 0;

      double deltaErrorEncdL = (errorEncdL - prevErrorEncdL);
      double deltaErrorEncdR = (errorEncdR - prevErrorEncdR);

      targPowerL = errorEncdL * kP + integralL * kI + deltaErrorEncdL * kD;
      targPowerR = errorEncdR * kP + integralR * kI + deltaErrorEncdR * kD;

      prevErrorEncdL = errorEncdL;
      prevErrorEncdR = errorEncdR;

      double deltaPowerL = targPowerL - powerL;
      powerL += abscap(deltaPowerL, RAMPING_POW);
      double deltaPowerR = targPowerR - powerR;
      powerR += abscap(deltaPowerR, RAMPING_POW);

      powerL = abscap(powerL, MAX_POW);
      powerR = abscap(powerR, MAX_POW);

      lf_wheel.move_velocity(powerL);
      lf_wheel.move_velocity(powerL);
    }
    pros::delay(dT);
  }

  return 0;
}

void resetCoords(double x, double y, double angleInDeg){
	pros::Motor lf_wheel (lf_port);
  pros::Motor rf_wheel (rf_port);
  resetPrevEncd();

  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angleInDeg);
}