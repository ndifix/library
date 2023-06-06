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

  basic_Matrix<T, Row, Col>& operator+(const basic_Matrix<T, Row, Col> &m) const;
  basic_Matrix<T, Row, Col>& operator-(const basic_Matrix<T, Row, Col> &m) const;
  template<size_t Col2>
  basic_Matrix<T, Row, Col2>& operator*(const basic_Matrix<T, Col, Col2> &m) const;
  basic_Matrix<T, Row, Col>& operator*(const double scalar) const;
  void operator+=(const basic_Matrix<T, Row, Col> &m);
  void operator-=(const basic_Matrix<T, Row, Col> &m);
  void operator*=(const basic_Matrix<T, Row, Col> &m);
  void operator*=(const double scalar);

  basic_Vector<T, Col>& operator*(const basic_Vector<T, Row> &v) const;

  basic_Vector<T, Col>& operator[](const int r) const;

  template <typename U, size_t R, size_t C>
  friend std::ostream &operator<<(std::ostream &os, const basic_Matrix<U, R, C> &m);

#pragma endregion

#pragma region Methods

  bool isSquare() const;

  T det() const;

  T cofactor(int i, int j) const;

#pragma endregion
};  // end of basic_Matrix

template <class T, size_t Deg>
class basic_Vector : public std::array<T, Deg> {
 public:

#pragma region Operators

  basic_Vector<T, Deg>& operator+(const basic_Vector<T, Deg> &v) const;
  basic_Vector<T, Deg>& operator-(const basic_Vector<T, Deg> &v) const;
  basic_Vector<T, Deg>& operator*(const double scalar) const;

  template <class U, size_t D>
  friend basic_Vector<U, D>& operator*(const double scalar, const basic_Vector<U, D> &v);

  void operator+=(const basic_Vector<T, Deg> &v);
  void operator-=(const basic_Vector<T, Deg> &v);
  void operator*=(const double scalar);
  T &operator[](const int i) const;

  template <typename U, size_t D>
  friend std::ostream &operator<<(std::ostream &os, const basic_Vector<U, D> &v);

#pragma endregion
};

}  // namespace ndifix

#endif
