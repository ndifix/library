#ifndef NDIFIX_COMPLEX
#define NDIFIX_COMPLEX

#include <iostream>

namespace ndifix {
class Complex {
 public:
  double Re, Im;

#pragma region Constructors

  Complex() { Re = Im = 0; }

  Complex(double r, double i) {
    Re = r;
    Im = i;
  }

  Complex(double r) {
    Re = r;
    Im = 0;
  }

#pragma endregion

#pragma region Operator

  Complex operator+(Complex c) {
    Complex ret = *this;
    ret.Re += c.Re;
    ret.Im += c.Im;
    return ret;
  }

  Complex operator-(Complex c) { return operator+(c * -1); }

  Complex operator*(Complex c) {
    Complex ret;
    ret.Re = this->Re * c.Re - this->Im * c.Im;
    ret.Im = this->Re * c.Im + this->Im * c.Re;
    return ret;
  }

  Complex operator*(double r) {
    Complex ret = *this;
    ret.Re *= r;
    ret.Im *= r;
    return ret;
  }

  void operator+=(Complex c) { *this = operator+(c); }

  void operator-=(Complex c) { *this = operator-(c); }

  void operator*=(Complex c) { *this = operator*(c); }

  void operator*=(double r) { *this = operator*(r); }

  friend std::ostream &operator<<(std::ostream &os, const Complex &c);

#pragma endregion

#pragma region Methods

  /// <return>複素共役</return>
  Complex cc() {
    Complex ret = *this;
    ret.Im *= -1;
    return ret;
  }

#pragma endregion
};

std::ostream &operator<<(std::ostream &os, const Complex &c) {
  if (c.Im >= 0) {
    os << c.Re << '+' << c.Im << 'i';
  } else if (c.Im < 0) {
    os << c.Re << '-' << c.Im << 'i';
  }

  return os;
}

}  // namespace ndifix

#endif
