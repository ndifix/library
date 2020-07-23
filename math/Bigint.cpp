#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ndifix {
class Bigint {
 private:
  std::vector<int> num;  // num[i]= k*(mod^i)
  const int mod = 10000;
  const int intmax = 1e8;
  const int modd = 4;  // 10^4
 public:
#pragma region Constructor

  Bigint() { num.push_back(0); };

  Bigint(int n) {
    num.push_back(n % mod);
    num.push_back((n / mod) % mod);
    num.push_back((n / mod / mod) % mod);
    shrink();
  }

  Bigint(long long n) {
    long long m = n;
    while (m) {
      num.push_back(m % mod);
      m /= mod;
    }
    modify();
  }

#pragma endregion

#pragma region BooleanOperators

  bool operator<(Bigint B) {
    if (size() != B.size()) {
      return size() < B.size();
    }
    for (int i = size() - 1; i >= 0; i--) {
      if (num[i] != B[i]) {
        return num[i] < B[i];
      }
    }
    return false;
  }

  bool operator>(Bigint B) {
    if (size() != B.size()) {
      return size() > B.size();
    }
    for (int i = size() - 1; i >= 0; i--) {
      if (num[i] != B[i]) {
        return num[i] > B[i];
      }
    }
    return false;
  }

  bool operator==(Bigint B) {
    if (size() != B.size()) {
      return false;
    }
    for (int i = size() - 1; i >= 0; i--) {
      if (num[i] != B[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator<=(Bigint B) { return !operator>(B); }

  bool operator>=(Bigint B) { return !operator<(B); }

  bool operator!=(Bigint B) { return !operator==(B); }

#pragma endregion

#pragma region Operators

  Bigint operator+(Bigint B) {
    Bigint ret = (*this);
    if (ret.size() < B.size()) ret.resize(B.size());
    for (int i = 0; i < (ret.size() < B.size() ? ret.size() : B.size()); i++)
      ret[i] += B[i];
    ret.modify();
    return ret;
  }

  Bigint operator-(Bigint &B) {
    Bigint ret(0);
    if (*this < B) {
      return ret;
    }
    ret = *this;
    for (int i = 0; i < std::min(ret.size(), B.size()); i++) {
      ret[i] -= B[i];
    }
    ret.modify();
    return ret;
  }

  Bigint operator*(Bigint &B) {
    Bigint ret(0);
    int s = size();
    Bigint buf;
    buf.resize(s);
    for (int i = 0; i < B.size(); i++) {
      buf.resize(0);
      buf.resize(s);
      for (int j = 0; j < s; j++) {
        buf.num[j] = B[i] * num[j];
      }
      buf.modify();
      buf <<= i;
      ret += buf;
      ret.modify();
    }
    return ret;
  }

  void operator+=(Bigint &B);
  // { *this = operator+(B); }

  void operator*=(Bigint &B);
  // { (*this) = operator*(B); }

  Bigint operator+(int n);
  // { return *this + Bigint(n); }

  Bigint operator-(int n);
  // { return operator+(n * -1); }

  void operator+=(int n);
  // { *this += Bigint(n); }

  Bigint operator*(int n) {
    Bigint B(n);
    return B * (*this);
  }

  void operator*=(int n) {
    Bigint B(n);
    (*this) = (*this) * B;
  }

  Bigint operator/(int n);

  int operator%(int n) {
    Bigint ret = *this, buf;
    long long tmp = 1, tmp2;
    while (ret >= n) {
      buf = 0;
      for (int i = 0; i < ret.size(); i++) {
        tmp2 = ret[i] * tmp;
        tmp2 %= n;
        buf += tmp2;
        tmp *= mod;
        tmp %= n;
      }
      ret = buf;
    }
    return ret.num[0];
  }

  void operator%=(int n) {
    Bigint ret = *this, buf;
    long long tmp = 1, tmp2;
    while (ret >= n) {
      buf = 0;
      for (int i = 0; i < ret.size(); i++) {
        tmp2 = ret[i] * tmp;
        tmp2 %= n;
        buf += tmp2;
        tmp *= mod;
        tmp %= n;
      }
      ret = buf;
    }
    (*this) = ret;
  }

  Bigint operator/(Bigint &B);

  Bigint operator<<(int i) {
    Bigint ret = (*this);
    for (int j = 0; j < i; j++) ret.num.insert(num.begin(), 0);
    return ret;
  }

  void operator<<=(int i) {
    for (int j = 0; j < i; j++) num.insert(num.begin(), 0);
  }

  Bigint operator=(Bigint &B) { *this = B; }

  void operator=(int n);
  // { *this = Bigint(n); }

  int &operator[](int i) { return num[i]; }
  std::string to_str() {
    std::string ret, buf_s;
    int buf = num[num.size() - 1];
    ret += std::to_string(buf);
    for (int i = num.size() - 2; i >= 0; i--) {
      buf = num[i];
      buf_s = std::to_string(buf);
      while (buf_s.size() != modd) buf_s.insert(buf_s.begin(), '0');
      ret += buf_s;
      buf_s.clear();
    }
    return ret;
  }

  friend std::ostream &operator<<(std::ostream &os, Bigint &B);

#pragma endregion

#pragma region Methods
  int size() { return int(num.size()); }

  void resize(int size) { num.resize(size); }

  void shrink() {
    while (num.size() >= 2 && num.back() == 0) num.pop_back();
  }

  void modify() {
    shrink();
    int tmp;
    for (int i = 0; i < num.size() - 1; i++) {
      if (num[i] < 0) {
        tmp = (-1) * num[i];
        tmp += (tmp / mod) + !!(tmp % mod);
        num[i + 1] -= tmp;
        num[i] += tmp * mod;
      }
    }
    if (num.back() == 0) {
      num.resize(1);
      num[0] = 0;
    }
    shrink();
    num.resize(num.size() + 1);
    for (int i = 0; i < num.size() - 1; i++) {
      if (num[i] >= mod) {
        num[i + 1] += (num[i] / mod);
        num[i] = num[i] % mod;
      }
    }
    shrink();
  }

  std::string toString() {
    std::stringstream ss;
    for (auto itr = num.rbegin(); itr != num.rend(); itr--) {
      ss << *itr;
    }

    return ss.str();
  }

#pragma endregion
};  // end of Bigint

std::ostream &operator<<(std::ostream &os, Bigint &B) {
  os << B.toString();
  return os;
}

}  // namespace ndifix