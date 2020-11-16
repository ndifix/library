#ifndef NDIFIX_PICTURE_JPEG_IMAGEDATA
#define NDIFIX_PICTURE_JPEG_IMAGEDATA

#include <fstream>
#include <vector>

#include "../Utility.cpp"

namespace ndifix {

class ImageData {
 private:
  std::vector<char> binary;

 public:
  void ReadImageData(std::ifstream& ifs) {
    std::cout << "Image Data\t";
    bool end = false;
    while (true) {
      char c;
      ifs.get(c);
      if (end && c != (char)0x00) {
        binary.pop_back();
        ifs.seekg(-2, std::ios::cur);
        break;
      }
      if (c == (char)0xff) {
        end = true;
      } else {
        end = false;
      }
      binary.push_back(c);
    }

    std::cout << binary.size() << "Bytes" << std::endl;

    if (DebugBinaryImageData) ShowBin();
  }

  void ShowBin() {
    for (int i = 0; i < binary.size(); i++) {
      PrintHex(binary[i]);
      if (i % 16 == 15)
        std::cout << std::endl;
      else
        std::cout << " ";
    }
    std::cout << std::endl << std::endl << std::dec;
  }
};

}  // namespace ndifix

#endif
