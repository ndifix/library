#ifndef NDIFIX_MATRIX
#define NDIFIX_MATRIX

#include "../template/Matrix.cpp"

#include <iostream>
#include <vector>

namespace ndifix {

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
