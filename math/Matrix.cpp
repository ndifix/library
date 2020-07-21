#ifndef NDIFIX_MATRIX
#define NDIFIX_MATRIX

#include "../template/Matrix.cpp"

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

  operator Cmatrix() {
    Cmatrix ret(this->row, this->collumn);
    for (int i = 0; i < this->row; i++) {
      for (int j = 0; j < this->collumn; j++) {
        ret[i][j] = Complex(this->data[i][j]);
      }
    }
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
};

}  // namespace ndifix

#endif
