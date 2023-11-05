#include "control.h"
#include "main.h"
#include "constants.h"

extern double baseWidth;
extern double X, Y, theta, prevEncdL, prevEncdR, prevAngle;
extern double angle, lastResetAngle;
extern double inPerDeg;
extern double torad;
extern double encdL;
extern double encdR;

extern double targetX, targetY, targettheta;
extern double errorX, errorY, errortheta;
extern double errdisp, preverrdisp, totalerr;
extern double powerL, powerR;
extern double targPowerL, targPowerR;
extern double kP, kD , kI;

extern double pi;
extern double halfpi;
extern double doublepi;

extern double targEncdL, targEncdR;
extern double errorEncdL, errorEncdR;
extern double powerL, powerR;
extern double targPowerL, targPowerR;
extern double kP, kD, kI;

extern bool turnmode = false;
extern bool drivemode = false;
extern bool stationarymode = false;

extern double totalthetaerr = 0;
extern double prevthetaerr = 0;

double prevErrorX, prevErrorY;
double targLeft, targRight;


//input x and y values then robot turn to that position first before moving in a straight line
int Control(){
  using namespace pros;
  Motor lf_base(lf_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lt_base(lt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lb_base(lb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rf_base(rf_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rt_base(rt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rb_base(rb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

  //Motor lf_wheel (lf_port);
  //Motor rf_wheel (rf_port);
  while(true){
    //constantly check if robot needs to turn or move
    //rotate if turnmode=true
    if (turnmode){
      //runs until within range of +-1 degrees of target theta
      while (fabs(theta/torad - targettheta/torad) > 1){
        errortheta = targettheta - theta;
        totalthetaerr += errortheta;

        double turnder = errortheta - prevthetaerr;
        double turnvoltage = (double) -75 * errortheta + (double) 0.001 * totalthetaerr + (double) 2500 * turnder;
     
        lf_base.move(turnvoltage);
        rf_base.move(turnvoltage);		

        printf("turnPID:%f  theta: %f    targettheta: %f    errortheta: %f    turnmode: %d   totalerr: %f    der: %f\n",\
		    turnvoltage, theta/torad, targettheta/torad, errortheta/torad, turnmode, totalthetaerr, turnder/torad);

        prevthetaerr = errortheta;

        pros::delay(2);
      }
      turnmode = false;
      errortheta = targettheta - theta;
      prevthetaerr = 0;
      totalthetaerr = 0;
      lf_base.brake();
      rf_base.brake();
      pros::delay(2);
    }
    //double prevErrorLeft, prevErrorRight;
    //moves if drivemode=true
    // if (drivemode){
    //   //runs until errorX and errorY are +-0.2cm
    //   while (true){
    //     kP = 1;
    //     double errorLeft = targLeft - encdL;
    //     double errorRight = targRight - encdR;

    //     double deltaErrorLeft = errorLeft - prevErrorLeft;
    //     double deltaErrorRight = errorRight - prevErrorRight;

    //     double powerL = kP * errorLeft + kD* deltaErrorLeft;
    //     double powerR = kP * errorRight + kD * deltaErrorRight;

    //     //move to target displacement
    //     lf_wheel.move(powerL);
    //     rf_wheel.move(-powerR);
    //     printf("powerL %.2f, powerR %.2f \n", powerL, powerR);

    //     prevErrorLeft = errorLeft;
    //     prevErrorRight = errorRight;

    //     errorX = targetX - X;
    //     errorY = targetY - Y;
    //     if(errorX == 0){errorX += 0.001;} 
    //     double arcTan = errorY/errorX;
    //     fabs(targettheta = atan(arcTan));
    //     errortheta = targettheta - theta;
    //     printf("targetTheta %.2f \n" , targettheta);
    //     //checks if robot is moving off angle and corrects itself
    //     if ((errortheta/torad >= 5) or (errortheta/torad <= -5)){
    //       turnmode = true;
    //       break;
    //     }
    //     //calculate displacement error using pythagoras for kP

    //     double deltaErrorX = errorX - prevErrorX;
    //     double deltaErrorY = errorY - prevErrorY;

    //     errdisp = pow((pow(errorX,2) + pow(errorY,2)), 0.5);
    //     if (X > targetX or Y > targetY){
    //       errdisp *= -1;
    //     }
    //     // //calculate total error for kI
    //     totalerr += errdisp;

    //     double der = errdisp - preverrdisp;
    //     double voltage = 5 * errdisp + kD * der;
        
    //     printf("x:%f  y:%f Theta: %f errdisp: %f \n",\
		//     X, Y, theta/torad, errdisp);

    //     // //move to target displacement
    //     lf_wheel.move(voltage);
    //     rf_wheel.move(-voltage);

    //     //assign previous error for kD
    //     preverrdisp = errdisp;
         
    //     pros::delay(2);
    //   }
    //   //reset ID values after reaching
    //   if (turnmode == false){
    //     drivemode = false;
    //     totalerr = 0;
    //     preverrdisp = 0;
    //   }
    // }
     pros::delay(2);
  }
}

//function to set target X and Y values
void movecoords(double left, double right){
  targLeft = left;
  targRight = right;
  // errorX = targetX - X;
  // errorY = targetY - Y;
  // errdisp = pow((pow(errorX,2) + pow(errorY,2)), 0.5);
  drivemode = true;
}

//function to rotate robot about a fixed point
void rotateto(double degrees){
  targettheta = degrees * torad;
  errortheta = targettheta - theta;
  turnmode = true;
}


