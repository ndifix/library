#ifndef NDIFIX_JPEG_SEGMENT
#define NDIFIX_JPEG_SEGMENT

#include <fstream>
#include <string>
#include <vector>

#include "../RGB.cpp"
#include "../Utility.cpp"
#include "Marker.cpp"

namespace ndifix {

class Segment {
 protected:
  // marker 2 byte
  Marker marker;
  // length 2 byte
  int length;
  // segment paramater N=length-2 byte
  std::vector<char> param;

 public:
  Segment(Marker m) { marker = m; }
  Segment() {}

  void set(Marker m) { marker = m; }

  void ReadSegment(std::ifstream& ifs) {
    char f, s;
    ifs.get(f);
    ifs.get(s);
    length = GetInt(f, s);

    marker.print();
    std::cout << std::hex << "\t" << std::setfill('0') << std::right
              << std::setw(4) << length << std::endl
              << std::dec;
    param.resize(length - 2);
    for (auto& i : param) ifs.get(i);
    ShowData();
  }

  void ShowData() {
    for (auto i : param) PrintHex(i);
    std::cout << std::endl;
  }
};

class APP0 : public Segment {
 private:
  std::string ID;
  std::string Ver;
  // unit of resolution
  int U = 1;
  // resolution
  int Xd, Yd;
  // thumbnail size
  int Xt = 0, Yt = 0;
  // thumbnail
  RBGImage thumb;

  void setVer(char f, char s) {
    Ver += std::to_string(GetInt(0, f));
    Ver += ".";
    Ver += std::to_string(GetInt(0, s));
  }

 public:
  using Segment::Segment;

  void ReadSegment(std::ifstream& ifs) {
    Segment::ReadSegment(ifs);
    char id[5] = {param[0], param[1], param[2], param[3], param[4]};
    if (id == "JFIF") ID = "JFIF";
    setVer(param[5], param[6]);
    std::cout << "Ver: " << Ver << std::endl;
    U = GetInt(0, param[7]);
    Xd = GetInt(param[8], param[9]);
    Yd = GetInt(param[10], param[11]);
    Xt = GetInt(0, param[12]);
    Yt = GetInt(0, param[13]);
    thumb.resize(Xt, Yt);
    /*
    read thumbnail
    */

    std::cout << "U=" << U << std::endl;
    std::cout << "Xd=" << Xd << std::endl;
    std::cout << "Yd=" << Yd << std::endl;
    std::cout << "Xt=" << Xt << std::endl;
    std::cout << "Yt=" << Yt << std::endl;
  }
};

}  // namespace ndifix

#endif
