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

extern double totalthetaerr;
extern double prevthetaerr;


//input x and y values then robot turn to that position first before moving in a straight line
int Control(){
  using namespace pros;
  Motor lf_wheel (lf_port);
  Motor rf_wheel (rf_port);
  while(true){
    //check if robot needs to turn only or turn and move
    if ((theta/torad) >= ((targettheta/torad) + 0.5) or (theta/torad) <= ((targettheta/torad) - 0.5)){
      turnmode = true;
    } 
    if (targetX or targetY){
      drivemode = true;
    }
    
    //rotate if turnmode=true
    if (turnmode){
      //runs until within range of +-5 degrees of target theta
      while ((theta/torad) >= ((targettheta/torad) + 0.5) or (theta/torad) <= ((targettheta/torad) - 0.5)){
        if (drivemode == true){
          targettheta = atan(errorY/errorX);
        }
        else{
          errortheta = targettheta - theta;
          //totalthetaerr += errortheta;
        }
        // + (0.1 * totalthetaerr) + (5 * (errortheta - prevthetaerr))
        lf_wheel.move((-75 * errortheta));
        rf_wheel.move((-75 * errortheta));

        //prevthetaerr = errortheta;

        delay(2);
      }
      turnmode = false;
      errortheta = targettheta - theta;
      lf_wheel.brake();
      rf_wheel.brake();
      delay(50);
    }
  
    //moves if drivemode=true
    if (drivemode){
      //runs until errorX and errorY are within range of -0.2 and 0
      while ((errorX >= 0.2 or errorX <= -0.2) and (errorY >= 0.2 or errorY <= 0.2)){
        errorX = targetX - X;
        errorY = targetY - Y;
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
        
        //move to target displacement
        lf_wheel.move(kP * errdisp + kI * totalerr + kD * (errdisp - preverrdisp));
        rf_wheel.move(-1 * kP * errdisp + kI * totalerr + kD * (errdisp - preverrdisp));

        //assign previous error for kD
        preverrdisp = errdisp;

        delay(50);
      }
      //reset ID values after reaching
      totalerr = 0;
      preverrdisp = 0;
    }
    delay(50);
  }
}

//function to set target X and Y values
void movecoords(double x, double y){
  targetX = x;
  targetY = y;
  drivemode = true;
}

//function to rotate robot about a fixed point
void rotateto(double degrees){
  targettheta = degrees * torad;
  errortheta = targettheta - theta;
  turnmode = true;
}


