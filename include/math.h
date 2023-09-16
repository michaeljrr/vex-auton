#ifndef _PROS_MATH_H_
#define _PROS_MATH_H_
#define PI      3.14159265358979323846264338328
#define halfPI  1.57079632679489661923132169164
#define twoPI	  6.28318530717958647692528676656
/**
 * angle conversion from radians to degrees and vice versa
 * angleDeg = angle * toDeg
 * angle = angleDeg * toRad
 */
#define toDeg   57.2957795130823208767981548141
#define toRad   0.0174532925199432957692369076849
/** refer to mathUtils.cpp for function documentation */
double boundRad(double rad);
double boundDeg(double deg);
double abscap(double x, double abscap);
double min(double a, double b);
int sign(double x);
#endif