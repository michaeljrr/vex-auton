#include "main.h"
#include "api.h"
#include <cmath>
#include "global.hpp"


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