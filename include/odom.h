#ifndef _PROS_ODOM_H_
#define _PROS_ODOM_H_


extern const double dbaseline;
extern const double wheelrad;
extern double X, Y, prevEncdL, prevEncdR, prevAngle;
extern double angle, lastResetAngle;
extern double inPerDeg;
extern double torad;
extern double encdL;
extern double encdR;
extern double theta;
extern double pi;
extern bool resetcoords;

extern double dleft = 0;
extern double dright = 0;
double dcenter = 0;
int Odometry();
int guessMovement(double dleft, double dright);


#endif