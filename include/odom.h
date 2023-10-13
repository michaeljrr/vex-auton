#ifndef _PROS_ODOM_H_
#define _PROS_ODOM_H_

extern double X, Y, angle, lastResetAngle;
extern double dleft, dright;
void setCoords(double x, double y, double angle);
int Odometry();
void resetPrevEncd();
int guessMovement(double dleft, double dright);
#endif