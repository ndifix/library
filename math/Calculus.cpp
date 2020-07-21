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

// Jacobi法を用いて Ax=b を解きます。
Rvector JacobiMethod(Rmatrix A, Rvector b, double dx = 0.001) {
  if (!A.isSquare() || A.Row() != b.Deg()) {
    throw std::invalid_argument("行列またはベクトルのサイズが不正です。");
  }
  for (int i = 0; i < A.Row(); i++) {
    if (A[i][i] == 0) {
      throw std::invalid_argument(
          "対角成分に0が含まれているためJacobi法を使えません。");
    }
  }
  /*
  (L + D + U)x = b
  Dx = b - (L + U)x
  Dx_(n+1) = b - (L + U)x_n

  || x_(n+1) - x_n || < dx のときに終了する
  */
  Rvector current = b, next;
  Rmatrix L, D, U, D_inv;

  L = LDU_L(A);
  D = LDU_D(A);
  U = LDU_U(A);
  D_inv = D;
  for (int i = 0; i < D.Row(); i++) {
    D_inv[i][i] = 1 / D[i][i];
  }

  for (int i = 0; i < 100; i++) {
    next = D_inv * (b - (L + U) * current);

    // ベクトルの差を検証
    Rvector diff;
    diff = next - current;
    if (diff.Norm() < dx) {
      return next;
    }

    current = next;
  }
}

}  // namespace ndifix
