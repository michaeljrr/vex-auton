#include "odom.h"
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

const double baseWidth = 11;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
double angle = 0, lastResetAngle = 0;
double inPerDeg = 2.75/360;
double pi = 3.14159265358979;
double encdL = 0;
double encdR = 0;

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

void setCoords(double x, double y, double a){
    X = x;
    Y = y;
    lastResetAngle = a*toRad;
    angle = a*toRad;
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