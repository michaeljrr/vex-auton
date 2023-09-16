#ifndef _PROS_GLOBAL_H_
#define _PROS_GLOBAL_H_
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

//constants
const double baseWidth = 11;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
double angle = 0, lastResetAngle = 0;
double inPerDeg = 2.75/360;
double toRad = 3.14159265358979 / 180;
double pi = 3.14159265358979;
double halfPI = 3.14159265358979 / 2;
double encdL = 0;
double encdR = 0;

#endif