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
}  // namespace ndifix