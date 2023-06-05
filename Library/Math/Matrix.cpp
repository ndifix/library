#ifndef NDIFIX_MATRIX
#define NDIFIX_MATRIX

#include "../../Include/Library/Matrix.hpp"

#include <cmath>
#include <iostream>
#include <vector>

#include "Complex.cpp"

namespace ndifix {

// 複素行列を表します。
template <size_t Row, size_t Col>
class Cmatrix : public basic_Matrix<Complex, Row, Col> {
  using basic_Matrix<Complex, Row, Col>::basic_Matrix;

 public:
  Cmatrix operator=(basic_Matrix<Complex, Row, Col> m) {
    this->row = m.Row();
    this->collumn = m.Collumn();
    this->data = m.Data();
    return *this;
  }
};

// 複素ベクトルを表します。
template <size_t Deg>
class Cvector : public basic_Vector<Complex, Deg> {
  using basic_Vector<Complex, Deg>::basic_Vector;

 public:
  Cvector operator=(basic_Vector<Complex, Deg> m) {
    this->degree = m.Deg();
    this->data = m.Data();
    return *this;
  }

  // 標準エルミート内積を返します。
  Complex dotP(Cvector cv) {
    if (this->degree != cv.degree) {
      std::invalid_argument("ベクトルの次数が異なります");
    }
    Complex ret = 0;
    for (int i = 0; i < this->degree; i++) {
      ret += this->data[i] * (cv.data[i].cc());
    }

    return ret;
  }

  // 2ノルムを返します
  double Norm() { return std::sqrt(dotP(*this).Re); }
};

// 実行列を表します。
template <size_t Row, size_t Col>
class Rmatrix : public basic_Matrix<double, Row, Col> {
  using basic_Matrix<double, Row, Col>::basic_Matrix;
};

// 実ベクトルを表します。
template <size_t Deg>
class Rvector : public basic_Vector<double, Deg> {
  using basic_Vector<double, Deg>::basic_Vector;

  // 標準エルミート内積を返します。
  double dotP(Rvector rv) {
    if (this->degree != rv.degree) {
      std::invalid_argument("ベクトルの次数が異なります");
    }
    double ret = 0;
    for (int i = 0; i < this->degree; i++) {
      ret += this->data[i] * rv.data[i];
    }

    return ret;
  }

  // 2ノルムを返します。
  double Norm() { return std::sqrt(dotP(*this)); }
};
}  // namespace ndifix

#endif
