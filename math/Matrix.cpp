#include <iostream>
#include <vector>
namespace ndifix {

template <class T>
class Matrix {
 private:
  int row, collumn;
  void push_row(std::vector<int> v) {
    if (v.size() == collumn) data.push_back(v);
  }
  void push_collumn(std::vector<int> v) {
    if (v.size() == row) {
      for (int i = 0; i < row; i++) data[i].push_back(v[i]);
    }
  }

 protected:
  int DefaultSize = 2;
  std::vector<std::vector<T>> data;

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

  void operator+=(Matrix<T> m) {
    if (row != m.row || collumn != m.collumn)
      throw std::invalid_argument("行列のサイズが異なります。");
    for (int i = 0; i < row; i++)
      for (int j = 0; j < collumn; j++) {
        data[i][j] += m.data[i][j];
      }
  }
  void operator-=(Matrix<T> m) {
    if (row != m.row || collumn != m.collumn)
      throw std::invalid_argument("行列のサイズが異なります。");
    for (int i = 0; i < row; i++)
      for (int j = 0; j < collumn; j++) {
        data[i][j] -= m.data[i][j];
      }
  }
  Matrix<T> operator+(Matrix<T> m) {
    if (row != m.row || collumn != m.collumn)
      throw std::invalid_argument("行列のサイズが異なります。");
    Matrix<T> ret = (*this);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < collumn; j++) {
        ret.data[i][j] += m.data[i][j];
      }
    return ret;
  }
  Matrix<T> operator-(Matrix<T> m) {
    if (row != m.row || collumn != m.collumn)
      throw std::invalid_argument("行列のサイズが異なります。");
    Matrix<T> ret = (*this);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < collumn; j++) {
        ret.data[i][j] -= m.data[i][j];
      }
    return ret;
  }
  void operator*=(Matrix<T> m) {
    if (collumn != m.row)
      throw std::invalid_argument("行列のサイズが異なります。");
    Matrix<T> ret(row, m.collumn);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < m.collumn; j++)
        for (int k = 0; k < collumn; k++) {
          ret.data[i][j] += data[i][k] * m.data[k][j];
        }
    data = ret.data;
    row = ret.row;
    collumn = ret.collumn;
  }
  Matrix<T> operator*(Matrix<T> m) {
    if (collumn != m.row)
      throw std::invalid_argument("行列のサイズが異なります。");
    Matrix<T> ret(row, m.collumn);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < m.collumn; j++)
        for (int k = 0; k < collumn; k++)
          ret.data[i][j] += data[i][k] * m.data[k][j];
    return ret;
  }
  void operator=(std::vector<std::vector<T>> v) {
    data = v;
    row = v.size();
    if (row) collumn = v[0].size();
  }
  std::vector<T> &operator[](int r) {
    if (0 <= r && r < row) return data[r];
  }

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &m);

#pragma endregion

#pragma region Methods

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

template <class T>
class sqMatrix : public Matrix<T> {
 private:
  int size;

 public:
#pragma region Constructors

  sqMatrix() {
    size = this->DefaultSize;
    this->data.resize(size);
    for (int i = 0; i < size; i++) this->data[i].resize(size);
  }
  sqMatrix(int s) {
    if (s < 0) throw std::invalid_argument("行列のサイズが負になっています。");
    size = s;
    this->data.resize(size);
    for (int i = 0; i < size; i++) this->data[i].resize(size);
  }
  sqMatrix(std::vector<std::vector<T>> &v) {
    size = v.size();
    for (int i = 0; i < size; i++) {
      if (v[i].size() != size) {
        throw std::invalid_argument("正方行列になっていません。");
      }
    }
    this->data = v;
  }

#pragma endregion

#pragma region Methods

  T det() {}
  sqMatrix invert() {}
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const sqMatrix<U> &m);
  template <typename U>
  friend sqMatrix<U> tensor(sqMatrix<U> &, sqMatrix<U> &);

#pragma endregion
};  // end of sqMatrix

template <typename U>
std::ostream &operator<<(std::ostream &os, const sqMatrix<U> &m) {
  for (int i = 0; i < m.size; i++) {
    for (int j = 0; j < m.size; j++) {
      os << m.data[i][j];
      if (j != m.size - 1) os << "\t";
      if (i != m.size - 1 && j == m.size - 1) os << "\n";
    }
  }
  return os;
}
template <typename U>
sqMatrix<U> tensor(ndifix::sqMatrix<U> &a, sqMatrix<U> &b) {
  sqMatrix<U> ret(a.size * b.size);
  for (int ar = 0; ar < a.size; ar++) {
    for (int ac = 0; ac < a.size; ac++) {
      int m = a.data[ar][ac];
      for (int br = 0; br < b.size; br++) {
        for (int bc = 0; bc < b.size; bc++) {
          ret.data[ar * a.size + br][ac * a.size + bc] = m * b.data[br][bc];
        }
      }
    }
  }
  return ret;
}

}  // namespace ndifix
