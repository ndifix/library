#include <cmath>

double ellipse1(double k){
  double K;
  double a=1.0,b=std::sqrt(1-k*k);
  long double i=0.0;
  while(a-b >0.000001){
    double a0=a;
    a=(a+b)/2.0;
    b=std::sqrt(b*a0);
    i+=1.0;
  }
  double pi=std::acos(-1);
  K=pi/2.0/a;
  return K;
}

double ellipse2(double k){
  double E;
  double a=1.0,b=std::sqrt(1-k*k);
  long double i=0.0;
  double t=1.0-k*k/2.0;
  while(a-b >0.000001){
    double a0=a;
    a=(a+b)/2.0;
    b=std::sqrt(b*a0);
    t-=(a*a-b*b)*std::pow(2.0,i);
    i+=1.0;
  }
  double pi=std::acos(-1);
  E=pi/2.0/a*t;
  return E;
}



double K,E;//第1,2種完全楕円積分
double Kn;//長岡係数
void ellipse12(double k){
  double a=1.0,b=std::sqrt(1-k*k);
  long double i=0.0;
  double t=1.0-k*k/2.0;
  while(a-b >0.000001){
    double a0=a;
    a=(a+b)/2.0;
    b=std::sqrt(b*a0);
    t-=(a*a-b*b)*std::pow(2.0,i);
    i+=1.0;
  }
  double pi=std::acos(-1);
  K=pi/2.0/a;
  E=K*t;
  Kn=(1-k*k)/k/k*K - (1-2.0*k*k)/k/k*E -k;
  Kn*=4.0/3.0/pi/std::sqrt(1-k*k);
}