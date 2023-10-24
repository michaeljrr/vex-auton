#include "auton.h"
#include "main.h"
#include "constants.h"

using namespace pros;



//turn 180
//lf_wheel.move(60);
//rf_wheel.move(60);
//pros::delay(1000);

//exactly one tile forward
//lf_wheel.move(60);
//rf_wheel.move(-60);
//pros::delay(1100);

void blue10() {
  //rotateto(0);
  //movecoords(10, 10);
}

double prevErrorLeft = 0;
double prevErrorRight = 0;
double encdleft = 0;
double encdright = 0;
double errorLeft = 0;
double errorRight = 0;
double LEFTTARGET = 0;
double RIGHTTARGET = 0;

//2.5 units = 1 degree = 0.0034906585cm
//644457 units = 90cm
//2300units = 90cm
void pidvalues(double targleft, double targright){
  LEFTTARGET = targleft;
  RIGHTTARGET = targright;

  errorLeft = targleft;
  errorRight = targright;
}

void pidmove(){
  using namespace pros;
  //Motor lf_wheel (lf_port);
  //Motor rf_wheel (rf_port);
  Motor lf_base(lf_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lt_base(lt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lb_base(lb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rf_base(rf_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rt_base(rt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rb_base(rb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
  //25 units = 1cm
  //and fabs(errorRight) >= 50
  while (true){
    if (fabs(errorLeft) >= 50 ){
      while (fabs(errorLeft) >= 50 ){
        encdleft = lf_base.get_position();
        encdright = rf_base.get_position();

        errorLeft = LEFTTARGET - encdleft;
        errorRight = RIGHTTARGET - encdright;

        double deltaErrorLeft = errorLeft - prevErrorLeft;
        double deltaErrorRight = errorRight - prevErrorRight;

        double powerL = 1.5 * (errorLeft/25) + 0 * deltaErrorLeft;
        double powerR = 1.5 * (errorRight/25) + 0 * deltaErrorRight;

        lf_base.move(powerL);
        lt_base.move(powerL);
        lb_base.move(powerL);
        rf_base.move(powerL);
        rt_base.move(powerL);
        rb_base.move(powerL);
      
    
        printf("encdleft: %f encdright:%f errorleft:%f errorright:%f deltaerrleft:%f deltaerrright:%f \n",\
        encdleft, encdright, errorLeft, errorRight, deltaErrorLeft, deltaErrorRight);

        prevErrorLeft = errorLeft;
        prevErrorRight = errorRight;

        pros::delay(2);
      }
      lf_base.brake();
      lt_base.brake();
      lb_base.brake();
      rf_base.brake();
      rt_base.brake();
      rb_base.brake();
      printf("stopped");
    }
    pros::delay(2);
  }
}


void red10() {

  	Motor lf_wheel (2);
    Motor rf_wheel (rf_port);

    //exactly one tile forward
    lf_wheel.move(60);
    rf_wheel.move(-60);
    pros::delay(1100);

    lf_wheel.brake();
    rf_wheel.brake();
    pros::delay(300);

    lf_wheel.move(60);
    rf_wheel.move(-60);
    pros::delay(1000);

    lf_wheel.brake();
    rf_wheel.brake();
    pros::delay(300);


    //turn left
    lf_wheel.move(-60);
    rf_wheel.move(-60);
    pros::delay(500);

    lf_wheel.brake();
    rf_wheel.brake();
    pros::delay(300);

    lf_wheel.move(60);
    rf_wheel.move(-60);
    pros::delay(1100);

    lf_wheel.brake();
    rf_wheel.brake();
    pros::delay(300);

    lf_wheel.move(60);
    rf_wheel.move(-60);
    pros::delay(1100);

    lf_wheel.brake();
    rf_wheel.brake();
    pros::delay(300);
}