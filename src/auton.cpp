#include "auton.h"
#include "main.h"

//base
#define lf_port 1
#define lt_port 20
#define lb_port 19
#define rf_port 10
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
  	pros::Motor lf_wheel (lf_port);
    pros::Motor rf_wheel (rf_port);
    
    lf_wheel.move(10);
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
}