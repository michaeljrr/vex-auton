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
extern double kP, kD;
extern bool drivemode;
extern bool resetpid;
extern bool rollermode;
extern bool catamode;
//2.5 units = 1 degree = 0.0034906585cm
//644457 units = 90cm
//2300units = 90cm
void pidvalues(double targleft, double targright, double kp, double kd){
  LEFTTARGET = targleft;
  RIGHTTARGET = targright;

  kP = kp;
  kD = kd;

  errorLeft = targleft;
  errorRight = targright;

  drivemode = true;
}

void pidmove(){
  using namespace pros;
  //Motor lf_wheel (lf_port);
  //Motor rf_wheel (rf_port);
  Motor_Group left_motors({lf_port,lt_port,lb_port});
  Motor_Group right_motors({rf_port,rt_port,rb_port});
  

  Motor lf_base(lf_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lt_base(lt_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
	Motor lb_base(lb_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rf_base(rf_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rt_base(rt_port, pros::E_MOTOR_GEARSET_06, false, pros::E_MOTOR_ENCODER_DEGREES);
	Motor rb_base(rb_port, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);

  //25 units = 1cm
  //and fabs(errorRight) >= 50
  while (true){
    if (resetpid){
      lf_base.tare_position();
      rf_base.tare_position();
      errorLeft = 0;
      errorRight = 0;
      encdleft = lf_base.get_position();
      encdright = rf_base.get_position();
      printf("pid reset\n");
      resetpid = false;
    }
    if (drivemode){
      while (fabs(errorLeft) >= 20 ){
        if (rollermode){
          pros::Motor lr(lr_port);
          pros::Motor rr(rr_port);
          lr.move(100);
          rr.move(-100);
        }
        encdleft = lf_base.get_position();
        encdright = rf_base.get_position();

        errorLeft = LEFTTARGET - encdleft;
        errorRight = RIGHTTARGET - encdright;

        double deltaErrorLeft = errorLeft - prevErrorLeft;
        double deltaErrorRight = errorRight - prevErrorRight;

        double powerL = kP * (errorLeft/25) + kD * deltaErrorLeft;
        double powerR = kP * (errorRight/25) + kD * deltaErrorRight;

        lf_base.move(powerL);
        lt_base.move(powerL);
        lb_base.move(powerL);
        rf_base.move(powerR);
        rt_base.move(powerR);
        rb_base.move(powerR);
        
      
        printf("encdleft: %f encdright:%f errorleft:%f errorright:%f deltaerrleft:%f deltaerrright:%f drivemode:%d\n",\
        encdleft, encdright, errorLeft, errorRight, deltaErrorLeft, deltaErrorRight, drivemode);

        prevErrorLeft = errorLeft;
        prevErrorRight = errorRight;

        pros::delay(2);
      }
      lf_base.move_velocity(0);
      lt_base.move_velocity(0);
      lb_base.move_velocity(0);
      rf_base.move_velocity(0);
      rt_base.move_velocity(0);
      rb_base.move_velocity(0);
      // lf_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      // lt_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      // lb_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      // rf_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      // rt_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      // rb_base.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      printf("stopped\n");
      drivemode = false;
    }

    if (rollermode){
      pros::Motor lr(lr_port);
      pros::Motor rr(rr_port);
      lr.move(100);
      rr.move(-100);
    }

    if (catamode){

      pros::Motor lc(lc_port);
      pros::Motor rc(rc_port);
      pros::Rotation catarot(catarot_port);
      lc.move(100);
      rc.move(100);
      printf("cata moving\n");
      delay(2);
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