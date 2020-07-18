namespace ndifix {

// ∫[a,b]f(x)dx を計算します。
// 台形で近似。区間[a,b]をN等分。
double Integral(double (*f)(double), double a, double b) {
  int N = 10000;
  double ret = 0;
  double dx = (b - a) / N;
  for (int t = 0; t < N; t++) {
    ret += (f(a + t * dx) + f(a + (t + 1) * dx)) * dx / 2;
  }
  return ret;
}
}  // namespace ndifix
