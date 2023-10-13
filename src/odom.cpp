#include "odom.h"
#include "sensors.h"
#include "main.h"

extern const double dbaseline;
extern double X, Y, prevEncdL, prevEncdR, prevAngle;
extern double angle, lastResetAngle;
extern double inPerDeg;
extern double torad;
extern double encdL;
extern double encdR;
extern double dleft = 0;
extern double dright = 0;
double dcenter = 0;
extern double theta;

//base
#define lf_port 1
#define lt_port 20
#define lb_port 19
#define rf_port 9
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



void setCoords(double x, double y, double a){
    X = x;
    Y = y;
    lastResetAngle = a*torad;
    angle = a*torad;
}

int Odometry(){
  using namespace pros;
  Motor lf_wheel (lf_port);
  Motor rf_wheel (rf_port);
  
  while (true){
    //get encoder units
    encdL = lf_wheel.get_position();
    encdR = rf_wheel.get_position();

    double prevencdL = 0;
    double prevencdR = 0;

    //delay(500);

    if (encdL != prevencdL){
      //get.position() -> 2.5 units per degree
      //convert encoder units to distance (in cm)
      //distance travelled = wheel arc length = radius(cm) * theta(in rad)
      dleft = 6.985 * (encdL / 2.5) * torad;
      dright = 6.985 * (encdR / 2.5) * torad;
      dcenter = (dleft + dright) / 2;

      //Update X, Y and theta
      X += dcenter * cos(theta);
      Y += dcenter * sin(theta);
      theta += ((dright - dleft) / dbaseline);
    }

    lf_wheel.tare_position();
    rf_wheel.tare_position();
  }
}

int prevLeft, prevRight;

int guessMovement(double dleft, double dright){

  //To guess the movement of the robot (e.g. moving in a circle, an arc, forward, backward, etc)
  //mainly for debugging purposes
  if (dright > dleft && dleft > 0){return 1;} // moving in an arc motion to the left
  else if(dright < dleft && dright > 0){return 2;} //moving in an arc motion to the right
  else if(dright < 0 && dleft > 0){return 3;} //clockwise rotation (circle)
  else if(dright > 0 && dleft < 0 ){return 4;} //anticlockwise rotation (circle)
  else if(dright != 0 && dleft ==0){return 5;}//only right wheel moving
  else if(dleft != 0 && dright ==0){return 6;}//only left wheel moving
  else if(dleft == prevLeft && dright == prevRight){return 7;}//stationary
  else{//either going forward or backward because dright = dleft
    if(dright>0){return 8;}//going forward
    else{return 9;}//going backward
  }
  prevLeft = dleft;
  prevRight = dright;
}

void resetPrevEncd() {
  prevEncdL = encdL;
  prevEncdR = encdR;
}

/*
int Odometry(){
        pros::Motor lf_wheel (lf_port);
        pros::Motor rf_wheel (rf_port); 
        

    while (true){
        //get encoder units
        encdL = lf_wheel.get_position();
        encdR = rf_wheel.get_position();

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
    /** update prev variables 
    prevEncdL = encdL;
    prevEncdR = encdR;
    prevAngle = angle;
    pros::delay(5);
  }
  //return 0;
}
*/

