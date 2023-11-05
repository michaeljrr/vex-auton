#include "odom.h"
#include "constants.h"
#include "main.h"

extern const double dbaseline;
extern const double wheelrad;
extern double X, Y, prevEncdL, prevEncdR, prevAngle;
extern double angle, lastResetAngle;
extern double inPerDeg;
extern double torad;
extern double encdL;
extern double encdR;
extern double theta;
extern double pi;
extern bool resetcoords;

extern double dleft = 0;
extern double dright = 0;
double dcenter = 0;

int Odometry(){
  using namespace pros;
  //Motor lf_wheel (lf_port);
  //Motor rf_wheel (rf_port);
  Motor lf_base(lf_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lt_base(lt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lb_base(lb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rf_base(rf_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rt_base(rt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rb_base(rb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

  pros::ADIEncoder quadL ('C', 'D');
  pros::ADIEncoder quadR ('G', 'H');
  
  while (true){
    //get encoder units
    //get.position() -> 2.5 units per degree
    encdL = lf_base.get_position();
    encdR = rf_base.get_position();

    //resets coords if true
    if (resetcoords){
      resetcoords = false;
      X = 0;
      Y = 0;
    }

    //update X,Y,theta if there changes
    if (encdL != 0 or encdR != 0){
      //convert encoder units to distance (in cm)
      //distance travelled = wheel arc length = radius(cm) * theta(in rad)
      dleft = wheelrad * (encdL / 2.5) * torad;
      dright = -1 * wheelrad * (encdR / 2.5) * torad;
      dcenter = (dleft + dright) / 2;

      //updates X, Y and theta
      X += dcenter * cos(theta);
      Y += dcenter * sin(theta);
      theta += ((dright - dleft) / dbaseline);

      //makes sure theta stays within 360 degrees for readability
      if (theta > (2*pi)){
        theta -= 2*pi;
      }
      else if (theta < (-2*pi)){
        theta += 2*pi;
      }
    }
    //resets motor encoder values
    lf_base.tare_position();
    rf_base.tare_position();

    delay(50);
  }
}


/*
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
}*/

