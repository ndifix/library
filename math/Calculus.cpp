#include "Matrix.cpp"

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

// LDU分解をしてLを返します。
Rmatrix LDU_L(Rmatrix &m) {
  Rmatrix ret(m.Row(), m.Collumn());
  for (int i = 0; i < m.Row(); i++) {
    for (int j = 0; j < i; j++) {
      ret[i][j] = m[i][j];
    }
  }
  return ret;
}

// LDU分解をしてDを返します。
Rmatrix LDU_D(Rmatrix &m) {
  Rmatrix ret(m.Row(), m.Collumn());
  for (int i = 0; i < m.Row(); i++) {
    ret[i][i] = m[i][i];
  }

  return ret;
}

// LDU分解をしてUを返します。
Rmatrix LDU_U(Rmatrix &m) {
  Rmatrix ret(m.Row(), m.Collumn());
  for (int i = 0; i < m.Row(); i++) {
    for (int j = i + 1; j < m.Collumn(); j++) {
      ret[i][j] = m[i][j];
    }
  }
  return ret;
}

}  // namespace ndifix
