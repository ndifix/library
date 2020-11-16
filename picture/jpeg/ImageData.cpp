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
    while (true) {
      char c;
      ifs.get(c);

      if (c == (char)0xff) {
        ifs.get(c);
        if (c == (char)0xda || c == (char)0xc4 || c == (char)0xd9) {
          ifs.seekg(-2, std::ios::cur);
          break;
        }
        binary.push_back((char)0xff);
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
