#ifndef NDIFIX_JPEG_MARKER
#define NDIFIX_JPEG_MARKER

#include <fstream>

#include "../Utility.cpp"

namespace ndifix {

class Marker {
 private:
  char first, second;

 public:
  Marker() {}
  Marker(int f, int s) {
    first = f;
    second = s;
  }
  Marker(std::ifstream& ifs) {
    ifs.get(first);
    ifs.get(second);
  }

  void set(int f, int s) {
    first = f;
    second = s;
  }

  void set(std::ifstream& ifs) {
    ifs.get(first);
    ifs.get(second);
  }

  bool operator==(Marker m) {
    if (m.first == first && m.second == second)
      return true;
    else
      return false;
  }

  char operator[](int i) {
    if (i == 0) return first;
    if (i == 1) return second;
    throw std::out_of_range("index must be 0 or 1");
  }

  void print() {
    PrintHex(first);
    PrintHex(second);
  }
};

Marker Soi(0xff, 0xd8);
Marker Eoi(0xff, 0xd9);

Marker App0(0xff, 0xe0);
Marker App1(0xff, 0xe1);

Marker Dqt(0xff, 0xdb);
Marker Dht(0xff, 0xc4);
Marker Sof(0xff, 0xc0);
Marker Sos(0xff, 0xda);

}  // namespace ndifix

#endif
