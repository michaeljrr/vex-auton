#include "constants.h"

//constants to change depending on robot
//dbaseline (in cm) = width of robot from left wheel to right wheel
//wheelrad (in cm) = ra
extern const double dbaseline = 29;
extern const double wheelrad = 5;
extern double kP = 0.2, kD = 0, kI = 0;


//variables
extern double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
extern double angle = 0;

extern double encdL = 0;
extern double encdR = 0;
extern double theta = 3.14159265358979 / 2;

extern double targetX = 0, targetY = 0, targettheta = 0;
extern double errorX = 0, errorY = 0, errortheta = 0;
extern double errdisp = 0, preverrdisp = 0;
extern double totalerr = 0;
extern double powerL = 0, powerR = 0;
extern double targPowerL = 0, targPowerR = 0;

extern bool resetcoords = false;

extern double totalthetaerr = 10.0;
extern double prevthetaerr = 10.0;


//constants
extern double pi = 3.14159265358979323846264338328;
extern double halfpi = 1.57079632679489661923132169164;
extern double doublepi = 6.28318530717958647692528676656;
extern double inPerDeg = 2.75/360;
extern double torad = 3.14159265358979 / 180;
