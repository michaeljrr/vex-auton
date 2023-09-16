#ifndef _PROS_ODOM_H_
#define _PROS_ODOM_H_

extern double X, Y, angle, lastResetAngle;
void setCoords(double x, double y, double angle);
int Odometry();
void resetPrevEncd();
#endif