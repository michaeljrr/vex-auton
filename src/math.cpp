#include "main.h"
#include "api.h"

double boundRad(double rad){
  double res = fmod(rad, 2*pi);
  if(res < 0) res += 2*pi;
  return res;
}
double boundDeg(double deg){
  double res = fmod(deg, 360);
  if(res < 0) res += 360;
  return res;
}
double abscap(double x, double abscap){
  if(x > abscap) return abscap;
  else if(x < -abscap) return -abscap;
  else return x;
}

double min(double a, double b) {
  if(a>b) return b;
  else return a;
}

int sign(double x){
  if(fabs(x) <= 1/1e9) return 0;
  else if(x > 0) return 1;
  else return -1;
}