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
  rotateto(180);
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