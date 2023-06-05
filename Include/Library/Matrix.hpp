#ifndef NDIFIX_BASIC_MATRIX
#define NDIFIX_BASIC_MATRIX

#include <iostream>
#include <array>

namespace ndifix {
template <class T, size_t Row, size_t Col>
class basic_Matrix;
template <class T, size_t Deg>
class basic_Vector;

template <class T, size_t Row, size_t Col>
class basic_Matrix : public std::array<std::array<T, Col>, Row> {
 public:

#pragma region Operators

  basic_Matrix<T, Row, Col> operator+(basic_Matrix<T, Row, Col> m);
  basic_Matrix<T, Row, Col> operator-(basic_Matrix<T, Row, Col> m);
  template<size_t Col2>
  basic_Matrix<T, Row, Col2> operator*(basic_Matrix<T, Col, Col2> m);
  basic_Matrix<T, Row, Col> operator*(double scalar);
  void operator+=(basic_Matrix<T, Row, Col> m);
  void operator-=(basic_Matrix<T, Row, Col> m);
  void operator*=(basic_Matrix<T, Row, Col> m);
  void operator*=(double scalar);
  basic_Matrix<T, Row, Col> operator^(basic_Matrix<T, Row, Col> ma);

  basic_Vector<T, Col> operator*(basic_Vector<T, Row> v);

  basic_Vector<T, Col> &operator[](int r);

  template <typename U, size_t R, size_t C>
  friend std::ostream &operator<<(std::ostream &os, const basic_Matrix<U, R, C> &m);

#pragma endregion

#pragma region Methods

  bool isSquare();

  T det();

  T cofactor(int i, int j);

#pragma endregion
};  // end of basic_Matrix

template <class T, size_t Deg>
class basic_Vector : public std::array<T, Deg> {
 public:

#pragma region Operators

  basic_Vector<T, Deg> operator+(basic_Vector<T, Deg> v);
  basic_Vector<T, Deg> operator-(basic_Vector<T, Deg> v);
  basic_Vector<T, Deg> operator*(double scalar);

  template <class U, size_t D>
  friend basic_Vector<U, D> operator*(double scalar, basic_Vector<U, D> v);

  void operator+=(basic_Vector<T, Deg> v);
  void operator-=(basic_Vector<T, Deg> v);
  void operator*=(double scalar);
  T &operator[](int i);

  template <typename U, size_t D>
  friend std::ostream &operator<<(std::ostream &os, const basic_Vector<U, D> &v);

#pragma endregion
};

}  // namespace ndifix

#endif
