#ifndef NDIFIX_QUBIT
#define NDIFIX_QUBIT

#include "Matrix.cpp"

namespace ndifix {
class Qubit : public Cvector {
  using Cvector::Cvector;

 public:
#pragma region Operators

  Qubit operator=(basic_Vector<Complex> c) {
    this->degree = c.Deg();
    this->data = c.Data();
    return *this;
  }

  Qubit operator^(Qubit q) {
    Qubit t = *this;
    Qubit ret(t.degree * q.degree);
    for (int i = 0; i < t.degree; i++) {
      for (int j = 0; j < q.degree; j++) {
        ret[i * q.degree + j] = t[i] * q[j];
      }
    }

    return ret;
  }

  void operator^=(Qubit q) { *this = operator^(q); }

#pragma endregion
};
}  // namespace ndifix

#endif
