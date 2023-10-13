#include "sensors.h"


extern double dbaseline = 11;
extern double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
extern double angle = 0, lastResetAngle = 0;
extern double inPerDeg = 2.75/360;
extern double torad = 3.14159265358979 / 180;
extern double encdL = 0;
extern double encdR = 0;
extern double theta = 3.14159265358979 / 2;

extern double targEncdL = 0, targEncdR = 0;
extern double errorEncdL = 0, errorEncdR = 0;
extern double powerL = 0, powerR = 0;
extern double targPowerL = 0, targPowerR = 0;
extern double kP = DEFAULT_KP, kD = DEFAULT_KD, kI = DEFAULT_KI;

extern double pi = 3.14159265358979323846264338328;
extern double halfpi = 1.57079632679489661923132169164;
extern double doublepi = 6.28318530717958647692528676656;

