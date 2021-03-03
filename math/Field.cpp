#ifndef NDIFIX_MATH_FIELD
#define NDIFIX_MATH_FIELD

#include <cmath>
#include <sstream>

namespace ndifix {
template <int p>
// Z/pZ を表します。
class Z_p {
 private:
  int val;

  bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= sqrt(n); i += 2) {
      if (n % i == 0) return false;
    }
    return true;
  }

  // ax + by = 1 を満たす(x,y)を表します。
  void extGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
      x = 1;
      y = 0;
      return;
    }
    extGCD(b, a % b, y, x);
    y -= a / b * x;
    return;
  }

 public:
  Z_p() {
    if (!isPrime(p)) {
      std::stringstream ss;
      ss << "p=" << p << " は合成数です。";
      throw std::invalid_argument(ss.str());
    }
    val = 0;
  }

  Z_p(int v) {
    if (!isPrime(p)) {
      std::stringstream ss;
      ss << "p=" << p << " は合成数です。";
      throw std::invalid_argument(ss.str());
    }

    v += p * (abs(v) / p + 1);
    val = v % p;
  }

  // aの積に関する逆元を表します。
  Z_p<p> Inv(Z_p<p> a) {
    // ax + py = 1 となる x が求めるもの。
    int x, y;
    extGCD(a.Val(), p, x, y);
    Z_p<p> ret(x);
    return ret;
  }

#pragma region Operators

  Z_p<p> operator+(Z_p<p> a) {
    Z_p<p> ret;
    ret.val = (Val() + a.Val()) % p;
    return ret;
  }

  Z_p<p> operator-(Z_p<p> a) {
    Z_p<p> ret;
    ret.val = (Val() + p - a.Val()) % p;
    return ret;
  }

  Z_p<p> operator*(Z_p<p> a) {
    Z_p<p> ret;
    long long lv = val, la = a.val, lp = p;
    ret.val = (lv * la) % lp;
    return ret;
  }

  Z_p<p> operator/(Z_p<p> a) {
    if (a.val == 0) {
      throw std::invalid_argument("零除算。");
    }
    return operator*(Inv(a));
  }

  void operator+=(Z_p<p> a) { *this = operator+(a); }

  void operator-=(Z_p<p> a) { *this = operator-(a); }

  void operator*=(Z_p<p> a) { *this = operator*(a); }

  void operator/=(Z_p<p> a) { *this = operator/(a); }

  Z_p<p> operator++() {
    *this += 1;
    return *this;
  }

  Z_p<p> operator--() {
    *this -= 1;
    return *this;
  }

  Z_p<p> operator=(int a) {
    Z_p<p> ret(a);
    *this = ret;
    return ret;
  }

  template <int q>
  friend std::ostream &operator<<(std::ostream &os, const Z_p<q> &a);

#pragma endregion

  int Val() { return val; }
};

template <int q>
std::ostream &operator<<(std::ostream &os, const Z_p<q> &a) {
  os << a.val;
  return os;
}

}  // namespace ndifix

#endif
