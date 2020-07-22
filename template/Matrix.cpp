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

  basic_Matrix() {
    row = collumn = DefaultSize;
    data.resize(row);
    for (int i = 0; i < row; i++) data[i].resize(collumn);
  }
  basic_Matrix(int r, int c) {
    if (r < 0 || c < 0) throw std::invalid_argument("行列のサイズが不正です。");
    row = r;
    collumn = c;
    data.resize(row);
    for (int i = 0; i < row; i++) data[i].resize(collumn);
  }
  basic_Matrix(int size) {
    if (size < 0) throw std::invalid_argument("行列のサイズが不正です。");
    row = collumn = size;
    data.resize(size);
    for (int i = 0; i < size; i++) data[i].resize(size);
  }
  basic_Matrix(std::vector<std::vector<T>> &v) {
    data = v;
    row = data.size();
    row > 0 ? collumn = data[0].size() : collumn = 0;

    for (auto d : data) {
      if (d.size() != collumn) {
        throw std::invalid_argument("行列になっていません。");
      }
    }
  }

#pragma endregion

#pragma region Operators

  basic_Matrix<T> operator+(basic_Matrix<T> m) {
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

  basic_Matrix<T> operator-(basic_Matrix<T> m) {
    m *= -1;
    return operator+(m);
  }

  basic_Matrix<T> operator*(basic_Matrix<T> m) {
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

  basic_Matrix<T> operator*(int scalar) {
    basic_Matrix<T> ret = *this;
    for (auto &i : ret.data) {
      for (auto &j : i) {
        j *= scalar;
      }
    }
    return ret;
  }

  void operator+=(basic_Matrix<T> m) { *this = operator+(m); }

  void operator-=(basic_Matrix<T> m) { *this = operator-(m); }

  void operator*=(basic_Matrix<T> m) { *this = operator*(m); }

  void operator*=(int scalar) { *this = operator*(scalar); }

  basic_Matrix<T> operator^(basic_Matrix<T> ma) {
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

  operator basic_Vector<T>() {
    std::vector<T> v(row);
    for (int i = 0; i < row; i++) {
      v[i] = data[i][0];
    }

    basic_Vector<T> ret(v);
    return ret;
  }

  basic_Vector<T> operator*(basic_Vector<T> v) {
    return (basic_Vector<T>)operator*((basic_Matrix<T>)v);
  }

  std::vector<T> &operator[](int r) {
    if (0 <= r && r < row) {
      return data[r];
    } else {
      throw std::invalid_argument("Segmentaion Fault");
    }
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const basic_Matrix<U> &m);

#pragma endregion

#pragma region Properties

  int Row() { return row; }

  int Collumn() { return collumn; }

  std::vector<std::vector<T>> Data() { return data; };

#pragma endregion

#pragma region Methods

  bool isSquare() { return row == collumn; }

  T det() {
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

  T cofactor(int i, int j) {
    basic_Matrix<T> ret = *this;
    ret.data.erase(ret.data.begin() + i);
    ret.row--;
    for (int k = 0; k < ret.row; k++) {
      ret.data[k].erase(ret.data[k].begin() + j);
    }
    ret.collumn--;
    return (i + j) % 2 == 0 ? ret.det() : ret.det() * -1;
  }

#pragma endregion
};  // end of basic_Matrix

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
class basic_Vector {
 protected:
  int degree;
  std::vector<T> data;

 public:
#pragma region Constructors

  basic_Vector() {}

  basic_Vector(int d) {
    degree = d;
    data.resize(degree);
  }

  basic_Vector(std::vector<T> &v) {
    degree = v.size();
    data = v;
  }

#pragma endregion

#pragma region Operators

  basic_Vector<T> operator+(basic_Vector<T> v) {
    if (degree != v.degree) {
      throw std::invalid_argument("ベクトルの次数が異なります。");
    }
    basic_Vector<T> ret = *this;
    for (int i = 0; i < ret.degree; i++) {
      ret[i] += v[i];
    }
    return ret;
  }

  basic_Vector<T> operator-(basic_Vector<T> v) { return operator+(v * -1); }

  basic_Vector<T> operator*(int scalar) {
    basic_Vector<T> ret = *this;
    for (int i = 0; i < ret.degree; i++) {
      ret[i] *= scalar;
    }
    return ret;
  }

  template <class U>
  friend basic_Vector<U> operator*(int scalar, basic_Vector<U> v);

  void operator+=(basic_Vector<T> v) { *this = operator+(v); }

  void operator-=(basic_Vector<T> v) { *this = operator-(v); }

  void operator*=(int scalar) { *this = operator*(scalar); }

  operator basic_Matrix<T>() {
    std::vector<std::vector<T>> v(degree, std::vector<T>(1));
    for (int i = 0; i < degree; i++) {
      v[i][0] = data[i];
    }
    basic_Matrix<T> ret(v);
    return ret;
  }

  T &operator[](int i) {
    if (i < 0 || i >= degree) {
      throw std::invalid_argument("Segmentaion Fault");
    }
    return data[i];
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const basic_Vector<U> &v);

#pragma endregion

#pragma region Properties

  int Deg() { return degree; }

  std::vector<T> Data() { return data; };

#pragma endregion
};

template <class U>
basic_Vector<U> operator*(int scalar, basic_Vector<U> v) {
  return v.operator*(scalar);
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const basic_Vector<U> &v) {
  for (int i = 0; i < v.degree; i++) {
    os << v.data[i] << (i != v.degree - 1 ? "\t" : "");
  }

  return os;
}

}  // namespace ndifix

#endif
