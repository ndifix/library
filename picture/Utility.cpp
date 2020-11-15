#ifndef NDIFIX_PICTURE_UTILITY
#define NDIFIX_PICTURE_UTILITY

#include <iomanip>
#include <iostream>

namespace ndifix {

bool DebugMode = true;

void PrintHex(char c) {
  std::cout << std::hex << (unsigned int)c % 256 / 16
            << (unsigned int)c % 256 % 16 << std::dec;
}

// 2Byte の値を整数値として取得
int GetInt(char f, char s) {
  return (((unsigned int)f % 256) << 8) + ((unsigned int)s % 256);
}

}  // namespace ndifix

#endif
