#ifndef NDIFIX_JPEG_MARKER
#define NDIFIX_JPEG_MARKER

#include <fstream>

#include "../Utility.cpp"

namespace ndifix {

class Marker {
 private:
  unsigned char sec;

 public:
  Marker() {}
  Marker(int s) { sec = (unsigned int)s % 256; }
  Marker(std::ifstream& ifs) {
    ifs.get();
    char c;
    ifs.get(c);
    sec = c;
  }

  void set(int s) { sec = (unsigned int)s % 256; }
  void set(std::ifstream& ifs) {
    ifs.get();
    char c;
    ifs.get(c);
    sec = c;
  }

  unsigned char get() { return sec; }

  bool operator==(Marker m) { return m.sec == sec; }

  bool isSOI() { return sec == 0xd8; }
  bool isEOI() { return sec == 0xd9; }
  bool isAPP() { return sec >= 0xe0 && sec <= 0xef; }
  bool isDQT() { return sec == 0xdb; }
  bool isDHT() { return sec == 0xc4; }
  bool isSOF() { return (sec / 16 == 12 && sec % 4 != 0) || sec == 0xc0; }
  bool isSOS() { return sec == 0xda; }
  bool isDRI() { return sec == 0xdd; }

  bool isSOF0() { return sec == 0xc0; }

  friend std::ostream& operator<<(std::ostream& os, Marker m);
};

std::ostream& operator<<(std::ostream& os, Marker m) {
  os << "ff" << std::hex << (unsigned int)m.sec << std::dec;
  return os;
}

}  // namespace ndifix

#endif
