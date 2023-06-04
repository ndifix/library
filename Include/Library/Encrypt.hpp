#ifndef NDIFIX_ENCRYPT_HPP
#define NDIFIX_ENCRYPT_HPP

#include <string>
#include <vector>

namespace ndifix {

class Base64 {
 private:
  // 6bitを文字に対応させる
  char
  BiToStr (
    std::string s6
    );

  // 文字を6bitに対応させる
  std::string
  StrToBi (
    char c
    );

  // 6 bit列を4文字に変換する。
  std::string
  Convert6To4 (
    std::vector<std::string> s6
    );

  // 6 bitごとに分割する。
  std::vector<std::string>
  SplitTo6 (
    std::string s
    );

  // 文字列を2進文字列に変換
  std::string
  EnToBi (
    std::string s
    );

  std::string
  Convert6ToStr (
    std::string sb
    );

  std::string
  ValidString (
    std::string s
    );

 public:
  std::string str;

  std::string
  Encode (
    std::string s
    );

  std::string
  Decode (
    std::string s
    );

  std::string
  Encode (
    );

  std::string
  Decode (
    );
};

}  // namespace ndifix

#endif
