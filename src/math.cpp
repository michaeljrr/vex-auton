#include "math.h"
#include "main.h"

extern double pi;
extern double doublepi;

extern double boundRad(double rad){
  double res = fmod(rad, doublepi);
  if(res < 0) res += 2*pi;
  return res;
}
extern double boundDeg(double deg){
  double res = fmod(deg, 360);
  if(res < 0) res += 360;
  return res;
}
extern double abscap(double x, double abscap){
  if(x > abscap) return abscap;
  else if(x < -abscap) return -abscap;
  else return x;
}

extern double min(double a, double b) {
  if(a>b) return b;
  else return a;
}

extern int sign(double x){
  if(fabs(x) <= 1/1e9) return 0;
  else if(x > 0) return 1;
  else return -1;
}