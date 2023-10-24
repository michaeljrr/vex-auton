#include "control.h"
#include "main.h"
#include "constants.h"


//input x and y values then robot turn to that position first before moving in a straight line
int Control(){
  using namespace pros;
  Motor lf_wheel (lf_port);
  Motor rf_wheel (rf_port);
  while(true){
    //constantly check if robot needs to turn or move

    //rotate if turnmode=true
    if (turnmode){
      //runs until within range of +-0.5 degrees of target theta
      while (fabs(theta - targettheta) > 0.5/torad){
        errortheta = targettheta - theta;
        totalthetaerr += errortheta;

        double turnder = errortheta - prevthetaerr;
        double turnvoltage = (double) -75 * errortheta + (double) 0.001 * totalthetaerr + (double) 250 * turnder;
     
        lf_wheel.move(turnvoltage);
        rf_wheel.move(turnvoltage);		

        printf("turnPID:%f  theta: %f    targettheta: %f    errortheta: %f    turnmode: %d   totalerr: %f    der: %f\n",\
		    turnvoltage, theta/torad, targettheta/torad, errortheta/torad, turnmode, totalthetaerr/torad, turnder/torad);

        prevthetaerr = errortheta;

        delay(2);
      }
      turnmode = false;
      errortheta = targettheta - theta;
      prevthetaerr = 0;
      totalthetaerr = 0;
      lf_wheel.brake();
      rf_wheel.brake();
      delay(2);
    }
  
    //moves if drivemode=true
    if (drivemode){
      //runs until errorX and errorY are +-0.2cm
      while (fabs(errorX) >= 0.2 and fabs(errorY) >= 0.2){
        errorX = targetX - X;
        errorY = targetY - Y;
        targettheta = atan(errorY/errorX);
        errortheta = targettheta - theta;
        //checks if robot is moving off angle and corrects itself
        if ((errortheta/torad >= 5) or (errortheta/torad <= -5)){
          turnmode = true;
          break;
        }
        //calculate displacement error using pythagoras for kP
        errdisp = pow((pow(errorX,2) + pow(errorY,2)), 0.5);
        //calculate total error for kI
        totalerr += errdisp;

        double der = errdisp - preverrdisp;
        
        printf("x:%f  y:%f Theta: %f errdisp: %f    totalerr: %f   turnmode:%d drivemode:%d pid:%f\n",\
		    X, Y, theta/torad, errdisp, totalerr, turnmode, drivemode, kP * errdisp + kI * totalerr + kD * der);

        //move to target displacement
        lf_wheel.move(kP * errdisp + kI * totalerr + kD * der);
        rf_wheel.move(kP * errdisp + kI * totalerr + kD * der);

        //assign previous error for kD
        preverrdisp = errdisp;

        delay(2);
      }
      //reset ID values after reaching
      if (turnmode == false){
        drivemode = false;
        totalerr = 0;
        preverrdisp = 0;
      }
    }
    delay(2);
  }
}

//function to set target X and Y values
void movecoords(double x, double y){
  targetX = x;
  targetY = y;
  errorX = targetX - X;
  errorY = targetY - Y;
  drivemode = true;
}

//function to rotate robot about a fixed point
void rotateto(double degrees){
  targettheta = degrees * torad;
  errortheta = targettheta - theta;
  turnmode = true;
}


