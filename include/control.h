#ifndef _PROS_CONTROL_H_
#define _PROS_CONTROL_H_


int Control();
void movecoords(double X, double Y);
void rotateto(double degrees);

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

#endif