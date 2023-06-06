#include "../../Include/Library/Matrix.hpp"

#include <iostream>
#include <vector>

namespace ndifix {

template <class T, size_t Row, size_t Col>
basic_Matrix<T, Row, Col>
basic_Matrix<T, Row, Col>::operator+ (
  basic_Matrix<T, Row, Col> m
  )
{
  basic_Matrix<T, Row, Col> ret = *this;
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col; j++) {
      ret.data[i][j] += m.data[i][j];
    }
  }
  return ret;
}

template <class T, size_t Row, size_t Col>
basic_Matrix<T, Row, Col>
basic_Matrix<T, Row, Col>::operator- (
  basic_Matrix<T, Row, Col> m
  )
{
  m *= -1;
  return operator+(m);
}

template <class T, size_t Row, size_t Col>
template <size_t Col2>
basic_Matrix<T, Row, Col2>
basic_Matrix<T, Row, Col>::operator* (
  basic_Matrix<T, Col, Col2> m
  )
{
  basic_Matrix<T, Row, Col2> ret;
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col2; j++) {
      for (int k = 0; k < Col; k++) {
        ret.data[i][j] += this->data[i][k] * m.data[k][j];
      }
    }
  }
  return ret;
}

template <class T, size_t Row, size_t Col>
basic_Matrix<T, Row, Col>
basic_Matrix<T, Row, Col>::operator* (
  double scalar
  )
{
  basic_Matrix<T, Row, Col> ret = *this;
  for (auto &i : ret.data) {
    for (auto &j : i) {
      j *= scalar;
    }
  }
  return ret;
}

template <class T, size_t Row, size_t Col>
void
basic_Matrix<T, Row, Col>::operator+= (
  basic_Matrix<T, Row, Col> m
  )
{
  *this = operator+(m);
}

template <class T, size_t Row, size_t Col>
void
basic_Matrix<T, Row, Col>::operator-= (
  basic_Matrix<T, Row, Col> m
  )
{
  *this = operator-(m);
}

template <class T, size_t Row, size_t Col>
void
basic_Matrix<T, Row, Col>::operator*= (
  basic_Matrix<T, Row, Col> m
  )
{
  *this = operator*(m);
}

template <class T, size_t Row, size_t Col>
void
basic_Matrix<T, Row, Col>::operator*= (
  double scalar
  )
{
  *this = operator*(scalar);
}

template <class T, size_t Row, size_t Col>
basic_Vector<T, Col>
basic_Matrix<T, Row, Col>::operator* (
  basic_Vector<T, Row> v
  )
{
  return (basic_Vector<T, Col>)operator*((basic_Matrix<T, Row, Col>)v);
}

template <class T, size_t Row, size_t Col>
basic_Vector<T, Col>&
basic_Matrix<T, Row, Col>::operator[] (
  int r
  )
{
  return this->at(r);
}

template <class T, size_t Row, size_t Col>
bool
basic_Matrix<T, Row, Col>::isSquare (
  )
{
  return Row == Col;
}

template <class T, size_t Row, size_t Col>
T
basic_Matrix<T, Row, Col>::det (
  )
{
  if (!isSquare()) {
    throw std::invalid_argument("正方行列ではありません。");
  }
  if (Row == 1 && Col == 1) {
    return this->data[0][0];
  }
  T ret = 0;
  for (int i = 0; i < Row; i++) {
    ret += this->data[i][0] * cofactor(i, 0);
  }

  return ret;
}

template <class T, size_t Row, size_t Col>
T
basic_Matrix<T, Row, Col>::cofactor (
  int i,
  int j
  )
{
  basic_Matrix<T, Row, Col> ret = *this;
  ret.data.erase(ret.data.begin() + i);
  ret.row--;
  for (int k = 0; k < ret.row; k++) {
    ret.data[k].erase(ret.data[k].begin() + j);
  }
  ret.collumn--;
  return (i + j) % 2 == 0 ? ret.det() : ret.det() * -1;
}

template <class T, size_t Row, size_t Col>
std::ostream&
operator<<(
  std::ostream &os,
  const basic_Matrix<T, Row, Col> &m
  )
{
  for (int i = 0; i < Row; i++) {
    for (int j = 0; j < Col; j++) {
      os << m.data[i][j];
      if (j != Col - 1) os << "\t";
      if (i != Row - 1 && j == Col - 1) os << "\n";
    }
  }
  return os;
}

template <class T, size_t Deg>
basic_Vector<T, Deg>
basic_Vector<T, Deg>::operator+ (
  basic_Vector<T, Deg> v
  )
{
  basic_Vector<T, Deg> ret = *this;
  for (int i = 0; i < Deg; i++) {
    ret[i] += v[i];
  }
  return ret;
}

template <class T, size_t Deg>
basic_Vector<T, Deg>
basic_Vector<T, Deg>::operator- (
  basic_Vector<T, Deg> v
  )
{
  return operator+(v * -1);
}

template <class T, size_t Deg>
basic_Vector<T, Deg>
basic_Vector<T, Deg>::operator* (
  double scalar
  )
{
  basic_Vector<T, Deg> ret = *this;
  for (int i = 0; i < ret.degree; i++) {
    ret[i] *= scalar;
  }
  return ret;
}

template <class T, size_t Deg>
void
basic_Vector<T, Deg>::operator+= (
  basic_Vector<T, Deg> v
  )
{
  *this = operator+(v);
}

template <class T, size_t Deg>
void
basic_Vector<T, Deg>::operator-= (
  basic_Vector<T, Deg> v
  )
{
  *this = operator-(v);
}

template <class T, size_t Deg>
void
basic_Vector<T, Deg>::operator*= (
  double scalar
  )
{
  *this = operator*(scalar);
}

template <class T, size_t Deg>
T&
basic_Vector<T, Deg>::operator[] (
  int i
  )
{
  return this->at(i);
}

template <class T, size_t Deg>
basic_Vector<T, Deg>
operator* (
  double scalar,
  basic_Vector<T, Deg> v
  )
{
  return v.operator*(scalar);
}

template <class T, size_t Deg>
std::ostream&
operator<< (
  std::ostream &os,
  const basic_Vector<T, Deg> &v
  )
{
  for (int i = 0; i < Deg; i++) {
    os << v.data[i] << (i != Deg - 1 ? "\t" : "");
  }

  return os;
}

}  // namespace ndifix
