#ifndef NDIFIX_JPEG
#define NDIFIX_JPEG

#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace ndifix {

void PrintHex(char c) {
  std::cout << std::hex << (unsigned int)c % 256 / 16
            << (unsigned int)c % 256 % 16 << std::dec;
}

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

Marker Dqt(0xff, 0xdb);
Marker Dht(0xff, 0xd4);
Marker Sof(0xff, 0xc0);
Marker Sos(0xff, 0xda);

class Segment {
 private:
  // marker 2 byte
  Marker marker;
  // length 2 byte
  int length;
  // segment paramater N=length-2 byte
  std::vector<char> param;

 public:
  Segment(Marker m) { marker = m; }

  void ReadSegment(std::ifstream& ifs) {
    char f, s;
    ifs.get(f);
    ifs.get(s);
    length = (((unsigned int)f % 256) << 8) + ((unsigned int)s % 256);

    marker.print();
    std::cout << std::hex << "\t" << std::setfill('0') << std::right
              << std::setw(4) << length << std::endl
              << std::dec;
    param.resize(length - 2);
    for (auto& i : param) ifs.get(i);
    ShowData();
  }

  void ShowData() {
    for (auto i : param) {
      // std::cout << std::bitset<8>(i).to_string();
      PrintHex(i);
    }
    std::cout << std::endl;
  }
};

class ImageData {
 private:
  std::vector<char> binary;

 public:
  void ReadImageData(std::ifstream& ifs) {
    bool end = false;
    while (true) {
      char c;
      ifs.get(c);
      if (end && c == Eoi[1]) {
        binary.pop_back();
        break;
      }
      if (c == Eoi[0]) {
        end = true;
      } else {
        end = false;
      }
      binary.push_back(c);
    }
    ShowBin();
  }

  void ShowBin() {
    std::cout << "Image Data" << std::endl;
    for (int i = 0; i < binary.size(); i++) {
      PrintHex(binary[i]);
      if (i % 16 == 15)
        std::cout << std::endl;
      else
        std::cout << " ";
    }
    std::cout << std::endl << std::dec;
  }
};

class Frame {
 private:
  std::vector<Segment> segments;
  ImageData imageData;

 public:
  Frame() {}
  Frame(std::string path) { ReadFrame(path); }

  void ReadFrame(std::string path) {
    std::ifstream ifs;
    try {
      ifs.open(path, std::ios::in | std::ios::binary);
      ifs.exceptions(std::ios::failbit);
    } catch (const std::exception& e) {
      std::cerr << "ファイルを開けませんでした。: " << e.what() << std::endl;
    }

    Marker marker(ifs);
    if (marker == Soi) {
      std::cout << "解析の開始" << std::endl;
      std::cout << "marker\tlength" << std::endl;
    } else {
      std::stringstream message;
      message << "開始マーカーが不整合。: ";
      message << std::hex;
      message << (unsigned int)marker[0] % 256;
      message << (unsigned int)marker[1] % 256;
      throw std::invalid_argument(message.str());
    }

    while (true) {
      marker.set(ifs);
      Segment seg(marker);
      seg.ReadSegment(ifs);
      segments.push_back(seg);

      if (marker == Sos) break;
    }

    imageData.ReadImageData(ifs);

    ifs.close();
  }
};

}  // namespace ndifix

#endif
