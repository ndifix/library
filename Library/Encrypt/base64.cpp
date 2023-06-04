#include <bitset>
#include <sstream>
#include <string>
#include <vector>

#include "../../Include/Library/Encrypt.hpp"

namespace ndifix {

char
Base64::BiToStr (
  std::string s6
  )
{
  int d = std::bitset<6>(s6).to_ulong();

  if (d < 26)
    return 'A' + d;
  else if (d < 26 + 26)
    return 'a' + d - 26;
  else if (d < 26 + 26 + 10)
    return '0' + d - 26 - 26;
  else if (d == 62)
    return '+';
  else
    return '/';
}

std::string
Base64::StrToBi (
  char c
  )
{
  int d;
  if ('A' <= c && c <= 'Z') d = c - 'A';
  if ('a' <= c && c <= 'z') d = c - 'a' + 26;
  if ('0' <= c && c <= '9') d = c - '0' + 52;
  if (c == '+') d = 62;
  if (c == '/') d = 63;

  return std::bitset<6>(d).to_string();
}

std::string
Base64::Convert6To4 (
  std::vector<std::string> s6
  )
{
  std::vector<std::string> vs(s6.size());
  for (int i = 0; i < s6.size(); i++) vs[i] = BiToStr(s6[i]);
  while (vs.size() % 4 != 0) vs.push_back("=");
  std::stringstream ret;
  for (auto i : vs) ret << i;
  return ret.str();
}

std::vector<std::string>
Base64::SplitTo6 (
  std::string s
  )
{
  std::vector<std::string> ret;
  while (s.size()) {
    ret.push_back(s.substr(0, std::min(6, (int)s.size())));
    s.erase(s.begin(), s.begin() + std::min(6, (int)s.size()));
  }

  while (ret.back().size() < 6) ret.back() += '0';
  return ret;
}

std::string
Base64::EnToBi (
  std::string s
  )
{
  std::vector<int> vi(s.size());
  for (int i = 0; i < s.size(); i++) vi[i] = s[i];

  std::string ret;
  for (auto i : vi) ret += std::bitset<8>(i).to_string();
  return ret;
}

std::string
Base64::Convert6ToStr (
  std::string sb
  )
{
  std::vector<int> vi(sb.size() / 8);
  while (sb.size() >= 8) {
    vi.push_back(std::bitset<8>(sb.substr(0, 8)).to_ulong());
    sb.erase(sb.begin(), sb.begin() + 8);
  }

  std::string ret;
  for (auto i : vi) ret += (char)i;
  return ret;
}

std::string
Base64::ValidString (
  std::string s
  )
{
  std::string ret;
  for (auto i : s) {
    if (33 <= i && i <= 126) ret += i;
  }
  return ret;
}

std::string
Base64::Encode (
  std::string s
  )
{
  std::vector<std::string> sixbits = SplitTo6(EnToBi(s));
  std::string ret = Convert6To4(sixbits);
  return ret;
}

std::string
Base64::Decode (
  std::string s
  )
{
  while (s.back() == '=') s.pop_back();

  std::string bits;
  for (auto i : s) bits += StrToBi(i);
  while (bits.size() % 8 != 0) bits.pop_back();

  std::string ret = Convert6ToStr(bits);

  return ValidString(ret);
}

std::string
Base64::Encode (
  )
{
  return Encode(str);
}

std::string
Base64::Decode (
  )
{
  return Decode(str);
}

}  // namespace ndifix
