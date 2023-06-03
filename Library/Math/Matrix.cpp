#ifndef NDIFIX_MATRIX
#define NDIFIX_MATRIX

#include "../template/Matrix.cpp"

#include <cmath>
#include <iostream>
#include <vector>

#include "Complex.cpp"

namespace ndifix {

// 複素行列を表します。
class Cmatrix : public basic_Matrix<Complex> {
  using basic_Matrix::basic_Matrix;

 public:
  Cmatrix operator=(basic_Matrix<Complex> m) {
    this->row = m.Row();
    this->collumn = m.Collumn();
    this->data = m.Data();
    return *this;
  }
};

// 複素ベクトルを表します。
class Cvector : public basic_Vector<Complex> {
  using basic_Vector::basic_Vector;

 public:
  Cvector operator=(basic_Vector<Complex> m) {
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
class Rmatrix : public basic_Matrix<double> {
  using basic_Matrix::basic_Matrix;

 public:
  Rmatrix operator=(basic_Matrix<double> m) {
    this->row = m.Row();
    this->collumn = m.Collumn();
    this->data = m.Data();
    return *this;
  }

  basic_Vector<double> operator*(basic_Vector<double> v) {
    basic_Matrix<double> rm = *this;
    return rm.operator*(v);
  }

  basic_Matrix<double> operator*(basic_Matrix<double> m) {
    basic_Matrix<double> rm = *this;
    return rm.operator*(m);
  }

  void operator*=(basic_Matrix<double> m) { *this = operator*(m); }

  basic_Vector<Complex> operator*(Cvector v) {
    Cmatrix cm = *this;
    return cm.operator*(v);
  }

  basic_Matrix<Complex> operator*(Cmatrix m) {
    Cmatrix cm = *this;
    return cm.operator*(m);
  }

  operator Cmatrix() {
    Cmatrix ret(this->row, this->collumn);
    for (int i = 0; i < this->row; i++) {
      for (int j = 0; j < this->collumn; j++) {
        ret[i][j] = Complex(this->data[i][j]);
      }
    }
    return ret;
  }
};

// 実ベクトルを表します。
class Rvector : public basic_Vector<double> {
  using basic_Vector::basic_Vector;

 public:
  Rvector operator=(basic_Vector<double> m) {
    this->degree = m.Deg();
    this->data = m.Data();
    return *this;
  }

  operator Cvector() {
    Cvector ret(this->degree);
    for (int i = 0; i < this->degree; i++) {
      ret[i] = Complex(this->data[i]);
    }
    return ret;
  }

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
