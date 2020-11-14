#ifndef NDIFIX_RGB
#define NDIFIX_RGB

#include <vector>

namespace ndifix {

class RGB {
 public:
  char R, G, B;
};

class RBGImage {
 private:
  // size
  int x, y;
  // image data
  std::vector<std::vector<RGB>> image;

 public:
  RBGImage(int x, int y) {
    this->x = x;
    this->y = y;
  }
  RBGImage() {}

  void resize(int x, int y) {
    this->x = x;
    this->y = y;
  }
};

}  // namespace ndifix

#endif
