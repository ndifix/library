#include <iostream>
#include <vector>
namespace ndifix {

template <class T>
class Matrix {
 private:
  int DefaultSize = 2;
  int row, collumn;
  std::vector<std::vector<T>> data;
  void push_row(std::vector<int> v) {
    if (v.size() == collumn) data.push_back(v);
  }
  void push_collumn(std::vector<int> v) {
    if (v.size() == row) {
      for (int i = 0; i < row; i++) data[i].push_back(v[i]);
    }
  }

 public:
#pragma region Constructors

  Matrix() {
    row = collumn = DefaultSize;
    data.resize(row);
    for (int i = 0; i < row; i++) data[i].resize(collumn);
  }
  Matrix(int r, int c) {
    if (r < 0 || c < 0) throw std::invalid_argument("行列のサイズが不正です。");
    row = r;
    collumn = c;
    data.resize(row);
    for (int i = 0; i < row; i++) data[i].resize(collumn);
  }
  Matrix(int size) {
    if (size < 0) throw std::invalid_argument("行列のサイズが不正です。");
    row = collumn = size;
    data.resize(size);
    for (int i = 0; i < size; i++) data[i].resize(size);
  }
  Matrix(std::vector<std::vector<T>> &v) {
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

  Matrix<T> operator+(Matrix<T> m) {
    if (row != m.row || collumn != m.collumn) {
      throw std::invalid_argument("行列のサイズが異なります。");
    }
    Matrix<T> ret = *this;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < collumn; j++) {
        ret.data[i][j] += m.data[i][j];
      }
    }
    return ret;
  }

  Matrix<T> operator-(Matrix<T> m) {
    m *= -1;
    return operator+(m);
  }

  Matrix<T> operator*(Matrix<T> m) {
    if (collumn != m.row) {
      throw std::invalid_argument("積を定義できないサイズです。");
    }
    Matrix<T> ret(row, m.collumn);
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < m.collumn; j++) {
        for (int k = 0; k < collumn; k++) {
          ret.data[i][j] += data[i][k] * m.data[k][j];
        }
      }
    }
    return ret;
  }

  Matrix<T> operator*(int scalar) {
    Matrix<T> ret = *this;
    for (auto &i : ret.data) {
      for (auto &j : i) {
        j *= scalar;
      }
    }
    return ret;
  }

  void operator+=(Matrix<T> m) { *this = operator+(m); }

  void operator-=(Matrix<T> m) { *this = operator-(m); }

  void operator*=(Matrix<T> m) { *this = operator*(m); }

  void operator*=(int scalar) { *this = operator*(scalar); }

  std::vector<T> &operator[](int r) {
    if (0 <= r && r < row) {
      return data[r];
    } else {
      throw std::invalid_argument("Segmentaion Fault");
    }
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &m);

#pragma endregion

#pragma region Methods

  bool isSquare() { return row == collumn; }

  T det() {}

  Matrix<T> invert() {}

  template <typename U>
  friend Matrix<U> kronecker(Matrix<U> &, Matrix<U> &);

#pragma endregion
};  // end of Matrix

template <class T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
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
Matrix<T> kronecker(Matrix<T> &a, Matrix<T> &b) {
  ndifix::Matrix<T> ret(a.row * b.row, a.collumn * b.collumn);
  for (int ar = 0; ar < a.row; ar++) {
    for (int ac = 0; ac < a.collumn; ac++) {
      int m = a.data[ar][ac];
      for (int br = 0; br < b.collumn; br++) {
        for (int bc = 0; bc < b.collumn; bc++) {
          ret.data[ar * a.row + br][ac * a.collumn + bc] = m * b.data[br][bc];
        }
      }
    }
  }
  return ret;
}

}  // namespace ndifix
