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

  int Val() { return val; }
};
}  // namespace ndifix

#endif
