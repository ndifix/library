#ifndef NDIFIX_JPEG_BASICSEGMENT
#define NDIFIX_JPEG_BASICSEGMENT

#include <fstream>
#include <string>
#include <vector>

#include "../Utility.cpp"
#include "Marker.cpp"

namespace ndifix {

class BasicSegment {
 protected:
  // marker 2 byte
  Marker marker;
  // length 2 byte
  int length;
  // segment paramater N=length-2 byte
  std::vector<char> param;

 public:
  BasicSegment(Marker m) { marker = m; }
  BasicSegment() {}

  void ReadSegment(std::ifstream& ifs) {
    char f, s;
    ifs.get(f);
    ifs.get(s);
    length = GetInt(f, s);

    param.resize(length - 2);
    for (auto& i : param) ifs.get(i);
  }

  void ShowData() {
    std::cout << "marker: " << marker;
    std::cout << std::hex << "\tlength: " << std::setfill('0') << std::right
              << std::setw(4) << length << std::dec << std::endl;
  }
};

typedef BasicSegment Segment;

}  // namespace ndifix

#endif
