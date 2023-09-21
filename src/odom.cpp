#include "odom.h"
#include "sensors.h"
#include "main.h"

extern const double baseWidth;
extern double X, Y, prevEncdL, prevEncdR, prevAngle;
extern double angle, lastResetAngle;
extern double inPerDeg;
extern double torad;
extern double encdL;
extern double encdR;

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


/**
 * angle conversion from radians to degrees and vice versa
 * angleDeg = angle * toDeg
 * angle = angleDeg * toRad
 */


void setCoords(double x, double y, double a){
    X = x;
    Y = y;
    lastResetAngle = a*torad;
    angle = a*torad;
}

int Odometry(){
        pros::Motor lf_wheel (lf_port);
        pros::Motor rf_wheel (rf_port); 
        

    while (true){
        //get encoder units
        encdL = lf_wheel.get_encoder_units();
        encdR = rf_wheel.get_encoder_units();

        //
        double encdChangeL = (encdL / 25.4)*inPerDeg;
        double encdChangeR = (encdR / 25.4)*inPerDeg;
        angle = lastResetAngle + ((encdL - encdR) / 25.4)*inPerDeg/baseWidth; //Theta = (s2-s1)/width
        double deltaAngle = angle - prevAngle;
        double sumEncdChange = encdChangeL + encdChangeR;

    if(deltaAngle == 0) //Cannot divide by 0
    {
			X += sumEncdChange/2*sin(angle);            	//Simple trigo
			Y += sumEncdChange/2*cos(angle);
		}
		else                //Refer to formulas
		{
			double halfDeltaAngle = deltaAngle/2;
			double strDist = (sumEncdChange/deltaAngle)*sin(halfDeltaAngle);
			X += strDist * sin(prevAngle+halfDeltaAngle);
			Y += strDist * cos(prevAngle+halfDeltaAngle);
		}
    /** update prev variables */
    prevEncdL = encdL;
    prevEncdR = encdR;
    prevAngle = angle;
    pros::delay(5);
  }
  return 0;
}

void resetPrevEncd() {
  prevEncdL = encdL;
  prevEncdR = encdR;
}