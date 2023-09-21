#include "auton.h"
#include "main.h"
#include "sensors.h"

void blue10() {
    resetCoords(0, 0, -58.3);
    baseMove(32);
    waitBase(1500);
      /*
  resetCoords(0, 0, -58.3);
  baseMove(32);
  waitBase(1500);
  // baseTurn(-27, 60, 0.3, 0, 10, false);
  baseTurn(1, 0.295, 0, 10);
  waitBase(2000);
  baseMove(32);
  waitBase(2000);
  baseTurn(-92, 0.29, 0, 10);
  waitBase(2000);
  baseMove(-23.5);
  waitBase(1200);
  // baseMove(10);
  // waitBase(1000);
  // baseTurn(-49, 0 , 0.29, 0, 10, false);
  baseTurn(-136, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(62.5, 0.14, 0, 5);
  waitBase(2000);
  intake(0);
  baseMove(-40, 0.14, 0, 5);
  intake(-30);
  waitBase(1500);
  // baseTurn(69, -2, 0.33, 0, 10, false);
  baseTurn(-246, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  intake(-5);
  baseMove(98, 0.15, 0, 10);
  waitBaseNoD(2500);
  baseMove(20);
  pros::delay(50);
  intake(-20);
  pros::delay(200); */
}

void red10() {

  //turn 180
    //lf_wheel.move(60);
    //rf_wheel.move(60);
    //pros::delay(1000);

    //exactly one tile forward
    //lf_wheel.move(60);
    //rf_wheel.move(-60);
    //pros::delay(1100);
    
  	pros::Motor lf_wheel (lf_port);
    pros::Motor rf_wheel (rf_port);

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

    //while(!((rf_wheel.get_position() < 105) && (rf_wheel.get_position() > 95))){
    //  pros::delay(10);
    }


    //resetCoords(0, 0, -58.3);
    //baseMove(32);
    //waitBase(1500);
    /*
  resetCoords(0, 0, -58.3);
  baseMove(32);
  waitBase(1500);
  // baseTurn(-27, 60, 0.3, 0, 10, false);
  baseTurn(1, 0.295, 0, 10);
  waitBase(2000);
  baseMove(32);
  waitBase(2000);
  baseTurn(-92, 0.29, 0, 10);
  waitBase(2000);
  baseMove(-23.5);
  waitBase(1200);
  // baseMove(10);
  // waitBase(1000);
  // baseTurn(-49, 0 , 0.29, 0, 10, false);
  baseTurn(-136, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  // intake(0);
  resetPrevEncd();
  baseMove(62.5, 0.14, 0, 5);
  waitBase(2000);
  baseMove(-40, 0.14, 0, 5);
  waitBase(1500);
  // baseTurn(69, -2, 0.33, 0, 10, false);
  baseTurn(-246, 0.285, 0, 10);
  waitBase(1500);
  // wait(500, msec);
  // resetPrevEncd();
  baseMove(98, 0.15, 0, 10);
  waitBaseNoD(2500);
  baseMove(20);
  pros::delay(50);
  pros::delay(200);
  */
