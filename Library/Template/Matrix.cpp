#include "../../Include/Library/Matrix.hpp"

#include <iostream>
#include <vector>

namespace ndifix {
template <class T>
basic_Matrix<T>::basic_Matrix() {
  row = collumn = DefaultSize;
  data.resize(row);
  for (int i = 0; i < row; i++) data[i].resize(collumn);
}
template <class T>
basic_Matrix<T>::basic_Matrix(int r, int c) {
  if (r < 0 || c < 0) throw std::invalid_argument("行列のサイズが不正です。");
  row = r;
  collumn = c;
  data.resize(row);
  for (int i = 0; i < row; i++) data[i].resize(collumn);
}
template <class T>
basic_Matrix<T>::basic_Matrix(int size) {
  if (size < 0) throw std::invalid_argument("行列のサイズが不正です。");
  row = collumn = size;
  data.resize(size);
  for (int i = 0; i < size; i++) data[i].resize(size);
}
template <class T>
basic_Matrix<T>::basic_Matrix(std::vector<std::vector<T>> &v) {
  data = v;
  row = data.size();
  row > 0 ? collumn = data[0].size() : collumn = 0;

  for (auto d : data) {
    if (d.size() != collumn) {
      throw std::invalid_argument("行列になっていません。");
    }
  }
}

template <class T>
basic_Matrix<T> basic_Matrix<T>::operator+(basic_Matrix<T> m) {
  if (row != m.row || collumn != m.collumn) {
    throw std::invalid_argument("行列のサイズが異なります。");
  }
  basic_Matrix<T> ret = *this;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < collumn; j++) {
      ret.data[i][j] += m.data[i][j];
    }
  }
  return ret;
}

template <class T>
basic_Matrix<T> basic_Matrix<T>::operator-(basic_Matrix<T> m) {
  m *= -1;
  return operator+(m);
}

template <class T>
basic_Matrix<T> basic_Matrix<T>::operator*(basic_Matrix<T> m) {
  if (collumn != m.row) {
    throw std::invalid_argument("積を定義できないサイズです。");
  }
  basic_Matrix<T> ret(row, m.collumn);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < m.collumn; j++) {
      for (int k = 0; k < collumn; k++) {
        ret.data[i][j] += data[i][k] * m.data[k][j];
      }
    }
  }
  return ret;
}

template <class T>
basic_Matrix<T> basic_Matrix<T>::operator*(double scalar) {
  basic_Matrix<T> ret = *this;
  for (auto &i : ret.data) {
    for (auto &j : i) {
      j *= scalar;
    }
  }
  return ret;
}

template <class T>
void basic_Matrix<T>::operator+=(basic_Matrix<T> m) {
  *this = operator+(m);
}

template <class T>
void basic_Matrix<T>::operator-=(basic_Matrix<T> m) {
  *this = operator-(m);
}

template <class T>
void basic_Matrix<T>::operator*=(basic_Matrix<T> m) {
  *this = operator*(m);
}

template <class T>
void basic_Matrix<T>::operator*=(double scalar) {
  *this = operator*(scalar);
}

template <class T>
basic_Matrix<T> basic_Matrix<T>::operator^(basic_Matrix<T> ma) {
  basic_Matrix<T> ret(row * ma.row, collumn * ma.collumn);
  for (int ar = 0; ar < row; ar++) {
    for (int ac = 0; ac < collumn; ac++) {
      int m = data[ar][ac];
      for (int br = 0; br < ma.collumn; br++) {
        for (int bc = 0; bc < ma.collumn; bc++) {
          ret.data[ar * row + br][ac * collumn + bc] = m * ma.data[br][bc];
        }
      }
    }
  }
  return ret;
}

template <class T>
basic_Vector<T> basic_Matrix<T>::operator*(basic_Vector<T> v) {
  return (basic_Vector<T>)operator*((basic_Matrix<T>)v);
}

template <class T>
std::vector<T> &basic_Matrix<T>::operator[](int r) {
  if (0 <= r && r < row) {
    return data[r];
  } else {
    throw std::invalid_argument("Segmentaion Fault");
  }
}

template <class T>
std::ostream &operator<<(std::ostream &os, const basic_Matrix<T> &m);

template <class T>
int basic_Matrix<T>::Row() {
  return row;
}

template <class T>
int basic_Matrix<T>::Collumn() {
  return collumn;
}

template <class T>
std::vector<std::vector<T>> basic_Matrix<T>::Data() {
  return data;
};

template <class T>
bool basic_Matrix<T>::isSquare() {
  return row == collumn;
}

template <class T>
T basic_Matrix<T>::det() {
  if (!isSquare()) {
    throw std::invalid_argument("正方行列ではありません。");
  }
  if (row == 1 && collumn == 1) {
    return data[0][0];
  }
  T ret = 0;
  for (int i = 0; i < row; i++) {
    ret += data[i][0] * cofactor(i, 0);
  }

  return ret;
}
template <class T>
T basic_Matrix<T>::cofactor(int i, int j) {
  basic_Matrix<T> ret = *this;
  ret.data.erase(ret.data.begin() + i);
  ret.row--;
  for (int k = 0; k < ret.row; k++) {
    ret.data[k].erase(ret.data[k].begin() + j);
  }
  ret.collumn--;
  return (i + j) % 2 == 0 ? ret.det() : ret.det() * -1;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const basic_Matrix<T> &m) {
  for (int i = 0; i < m.row; i++) {
    for (int j = 0; j < m.collumn; j++) {
      os << m.data[i][j];
      if (j != m.collumn - 1) os << "\t";
      if (i != m.row - 1 && j == m.collumn - 1) os << "\n";
    }
  }
  return os;
}

template <class T>
basic_Vector<T>::basic_Vector() {}

template <class T>
basic_Vector<T>::basic_Vector(int d) {
  degree = d;
  data.resize(degree);
}

template <class T>
basic_Vector<T>::basic_Vector(std::vector<T> &v) {
  degree = v.size();
  data = v;
}

template <class T>
basic_Vector<T> basic_Vector<T>::operator+(basic_Vector<T> v) {
  if (degree != v.degree) {
    throw std::invalid_argument("ベクトルの次数が異なります。");
  }
  basic_Vector<T> ret = *this;
  for (int i = 0; i < ret.degree; i++) {
    ret[i] += v[i];
  }
  return ret;
}

template <class T>
basic_Vector<T> basic_Vector<T>::operator-(basic_Vector<T> v) {
  return operator+(v * -1);
}

template <class T>
basic_Vector<T> basic_Vector<T>::operator*(double scalar) {
  basic_Vector<T> ret = *this;
  for (int i = 0; i < ret.degree; i++) {
    ret[i] *= scalar;
  }
  return ret;
}

template <class T>
basic_Vector<T> operator*(double scalar, basic_Vector<T> v);

template <class T>
void basic_Vector<T>::operator+=(basic_Vector<T> v) {
  *this = operator+(v);
}

template <class T>
void basic_Vector<T>::operator-=(basic_Vector<T> v) {
  *this = operator-(v);
}

template <class T>
void basic_Vector<T>::operator*=(double scalar) {
  *this = operator*(scalar);
}

template <class T>
T &basic_Vector<T>::operator[](int i) {
  if (i < 0 || i >= degree) {
    throw std::invalid_argument("Segmentaion Fault");
  }
  return data[i];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const basic_Vector<T> &v);

template <class T>
int basic_Vector<T>::Deg() {
  return degree;
}

template <class T>
std::vector<T> basic_Vector<T>::Data() {
  return data;
};

template <class T>
basic_Vector<T> operator*(double scalar, basic_Vector<T> v) {
  return v.operator*(scalar);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const basic_Vector<T> &v) {
  for (int i = 0; i < v.degree; i++) {
    os << v.data[i] << (i != v.degree - 1 ? "\t" : "");
  }

  return os;
}

}  // namespace ndifix
