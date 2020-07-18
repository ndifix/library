#include <cmath>
namespace ndifix {
struct phase {
  double x[3];  // x, vx, ax
  double y[3];

  double E() { return hypot(x[1], y[1]) / 2.0; }
};

// Euler法による積分を行う
// v = dx/dt = f(t) : f is given のときの t, x(t), v(t)を出力する。
// x0 は x(t0=0) の値
void EulerSteps(double (*f)(double), double x0, double t0 = 0) {
  double t, x = x0;
  double dt = 0.01;

  for (int times = 0; times < 10; times++) {
    t = t0 + dt * times;
    std::cout << t << "\t" << x << "\t" << f(t) << std::endl;

    x += f(t) * dt;
  }
}

// Leap-Frog法による積分を行う
// v = dx/dt = f(t) : f is given のときの t, x(t), v(t)を出力する。
// x0 は x(t0=0) の値
void LeapFrogSteps(double (*f)(double), double x0, double t0 = 0) {
  /*
  F(t+dt) = F(t) + dtf(t) + dt^2...
  F(t-dt) = F(t) - dtf(t) + dt^2...
  F(t+dt) = F(t-dt) + 2dtf(t)

  x3 = F(t+dt)  : 2 times t0+2dt
  x2 = F(t)     : 1 time  t0+dt
  x1 = F(t-dt)  : 0 times t0
  第一ステップはEuler法を使う
  */
  double t, x1, x2, x3;
  double dt = 0.01;

  t = t0 + dt;

  x1 = x0;
  std::cout << t - dt << "\t" << x1 << "\t" << f(t - dt) << std::endl;
  x2 = x1 + f(t - dt) * dt;
  std::cout << t << "\t" << x2 << "\t" << f(t) << std::endl;
  x3 = x1 + 2 * dt * f(t);
  std::cout << t + dt << "\t" << x3 << "\t" << f(t + dt) << std::endl;

  for (int times = 2; times < 10; times++) {
    t = t0 + dt * times;

    x1 = x2;
    x2 = x3;
    x3 = x1 + 2 * dt * f(t);
    std::cout << t + dt << "\t" << x3 << "\t" << f(t + dt) << std::endl;
  }
}
}  // namespace ndifix