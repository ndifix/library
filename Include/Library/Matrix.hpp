#ifndef NDIFIX_BASIC_MATRIX
#define NDIFIX_BASIC_MATRIX

#include <iostream>
#include <vector>

namespace ndifix {
template <class T>
class basic_Matrix;
template <class T>
class basic_Vector;

template <class T>
class basic_Matrix {
 private:
  int DefaultSize = 2;

 protected:
  int row, collumn;
  std::vector<std::vector<T>> data;

 public:
#pragma region Constructors

  basic_Matrix();
  basic_Matrix(int r, int c);
  basic_Matrix(int size);
  basic_Matrix(std::vector<std::vector<T>> &v);

#pragma endregion

#pragma region Operators

  basic_Matrix<T> operator+(basic_Matrix<T> m);
  basic_Matrix<T> operator-(basic_Matrix<T> m);
  basic_Matrix<T> operator*(basic_Matrix<T> m);
  basic_Matrix<T> operator*(double scalar);
  void operator+=(basic_Matrix<T> m);
  void operator-=(basic_Matrix<T> m);
  void operator*=(basic_Matrix<T> m);
  void operator*=(double scalar);
  basic_Matrix<T> operator^(basic_Matrix<T> ma);

  operator basic_Vector<T>();

  basic_Vector<T> operator*(basic_Vector<T> v);

  std::vector<T> &operator[](int r);

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const basic_Matrix<U> &m);

#pragma endregion

#pragma region Properties

  int Row();
  int Collumn();
  std::vector<std::vector<T>> Data();

#pragma endregion

#pragma region Methods

  bool isSquare();

  T det();

  T cofactor(int i, int j);

#pragma endregion
};  // end of basic_Matrix

template <class T>
std::ostream &operator<<(std::ostream &os, const basic_Matrix<T> &m);

template <class T>
class basic_Vector {
 protected:
  int degree;
  std::vector<T> data;

 public:
#pragma region Constructors

  basic_Vector();
  basic_Vector(int d);
  basic_Vector(std::vector<T> &v);

#pragma endregion

#pragma region Operators

  basic_Vector<T> operator+(basic_Vector<T> v);
  basic_Vector<T> operator-(basic_Vector<T> v);
  basic_Vector<T> operator*(double scalar);

  template <class U>
  friend basic_Vector<U> operator*(double scalar, basic_Vector<U> v);

  void operator+=(basic_Vector<T> v);
  void operator-=(basic_Vector<T> v);
  void operator*=(double scalar);
  T &operator[](int i);

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const basic_Vector<U> &v);

#pragma endregion

#pragma region Properties

  int Deg();

  std::vector<T> Data();

#pragma endregion
};

}  // namespace ndifix

#endif
