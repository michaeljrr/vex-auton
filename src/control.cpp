#include "control.h"
#include "main.h"

//base
#define lf_port 1
#define lt_port 20
#define lb_port 19
#define rf_port 10
#define rt_port 13
#define rb_port 15

//flipper
#define fs_port 9
#define fr_port 8
#define flipperrot_port 16

//cata
#define lc_port 3
#define rc_port 14
#define catarot_port 18

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

const double baseWidth = 11;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
double angle = 0, lastResetAngle = 0;
double inPerDeg = 2.75/360;
double torad = 3.14159265358979 / 180;
double pi = 3.14159265358979;
double half_pi = 3.14159265358979 / 2;
double encdL = 0;
double encdR = 0;

double targEncdL = 0, targEncdR = 0;
double errorEncdL = 0, errorEncdR = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD, kI = DEFAULT_KI;

#define PI      3.14159265358979323846264338328
#define halfPI  1.57079632679489661923132169164
#define twoPI	  6.28318530717958647692528676656
/**
 * angle conversion from radians to degrees and vice versa
 * angleDeg = angle * toDeg
 * angle = angleDeg * toRad
 */
#define toDeg   57.2957795130823208767981548141
#define toRad   0.0174532925199432957692369076849

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
  double error = a*torad - angle;
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

  double diff = a*torad*baseWidth/inPerDeg/2;
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
  printf("Turn to angle: %.2f\n", targAngle / torad);
	if(inverted) targAngle -= half_pi;
  // double diff = (targAngle - angle + lastResetAngle)*baseWidth/inPerDeg/2;
  // targEncdL += diff;
  // targEncdR += -diff;
  // kP = p;
  // kD = d;
  double diffAngle = boundRad(targAngle-angle);
  if(diffAngle > pi) diffAngle -= (2* pi);
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