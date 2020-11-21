#ifndef NDIFIX_PICTURE_JPEG_IMAGEDATA
#define NDIFIX_PICTURE_JPEG_IMAGEDATA

#include <bitset>
#include <fstream>
#include <vector>

#include "../Utility.cpp"
#include "Segment.cpp"

namespace ndifix {

class DataUnit {
 private:
  std::vector<std::vector<int>> block =
      std::vector<std::vector<int>>(8, std::vector<int>(8));

  int zz[8][8] = {
      {0, 1, 5, 6, 14, 15, 27, 28},     {2, 4, 7, 13, 16, 26, 29, 42},
      {3, 8, 12, 17, 25, 30, 41, 43},   {9, 11, 18, 24, 31, 40, 44, 53},
      {10, 19, 23, 32, 39, 45, 52, 54}, {20, 22, 33, 38, 46, 51, 55, 60},
      {21, 34, 37, 47, 50, 56, 59, 61}, {35, 36, 48, 49, 57, 58, 62, 63}};

  void modify(std::vector<char> &bin, std::string &buf) {
    while (bin.size() && buf.size() < 16) {
      buf += std::bitset<8>(bin[0]).to_string();
      bin.erase(bin.begin());
    }
  }

  int getVal(std::vector<char> &bin, std::string &buf, DHTTable table) {
    modify(bin, buf);
    int ret = 1e9;
    for (int i = 1; i <= 16; i++) {
      if (table.contains(buf.substr(0, i))) {
        ret = table.getVal(buf.substr(0, i));
        buf.erase(buf.begin(), buf.begin() + i);
        break;
      }
    }
    if (ret == 1e9) throw std::exception();
    return ret;
  }

  int getBits(std::vector<char> &bin, std::string &buf, int len) {
    modify(bin, buf);
    std::string s = buf.substr(0, len);
    buf.erase(buf.begin(), buf.begin() + len);
    int ret = std::bitset<16>(s).to_ulong();
    if (ret < (1 << len - 1)) {
      return ret + (-1 << len) + 1;
    } else {
      return ret;
    }
  }

 public:
  void ReadUnit(std::vector<char> &bin, std::string &buf, DHTTable dcTable,
                DHTTable acTable) {
    std::vector<int> uncoded;
    // get dc
    int val = getVal(bin, buf, dcTable);
    int ssss = val;
    uncoded.push_back(getBits(bin, buf, ssss));
    // get ac
    while (uncoded.size() < 64) {
      val = getVal(bin, buf, acTable);
      // EOB
      if (val == 0) {
        while (uncoded.size() < 64) uncoded.push_back(0);
        continue;
      }
      int run = val / 16;
      for (int i = 0; i < run; i++) uncoded.push_back(0);
      ssss = val % 16;
      uncoded.push_back(getBits(bin, buf, ssss));
    }

    for (int r = 0; r < 8; r++) {
      for (int c = 0; c < 8; c++) {
        block[r][c] = uncoded[zz[r][c]];
      }
    }

    if (DebugBinaryImageData) ShowUnit();
  }

  void ShowUnit() {
    for (int i = 0; i < 64; i++) {
      std::cout << block[i / 8][i % 8];
      if (i % 8 == 7)
        std::cout << std::endl;
      else
        std::cout << "\t";
    }
    std::cout << std::endl;
  }
};

class MCU {
  using HTables = std::vector<DHTTable>;

 private:
  int Nf;
  std::vector<int> H, V;
  std::vector<int> Td;
  std::vector<int> Ta;
  std::vector<DataUnit> blocks;

 public:
  MCU(SOF sof, SOS sos) {
    Nf = sof.getNf();
    H = sof.getH();
    V = sof.getV();
    Td = sos.getTd();
    Ta = sos.getTa();
  }

  void ReadMCU(std::vector<char> &bin, std::string &buf, HTables HuffTables) {
    for (int c = 0; c < Nf; c++) {
      DHTTable dc, ac;
      for (auto t : HuffTables) {
        if (t.getTc() == 0 && t.getTh() == Td[c]) dc = t;
        if (t.getTc() == 1 && t.getTh() == Ta[c]) ac = t;
      }
      for (int i = 0; i < H[c] * V[c]; i++) {
        DataUnit unit;
        unit.ReadUnit(bin, buf, dc, ac);
        blocks.push_back(unit);
      }
    }
  }
};

class ImageData {
 private:
  std::vector<char> binary;
  std::vector<std::vector<char>> bins;
  SOF sof;
  SOS sos;
  std::vector<MCU> mcus;
  std::vector<DHTTable> HuffTables;

  void readMCU() {
    for (int b = 0; b < bins.size(); b++) {
      auto bin = bins[b];
      std::string buf;
      while (bin.size() != 0 || buf.size() != 0) {
        if (bin.size() == 0) {
          break;
        }
        MCU mcu(sof, sos);
        mcu.ReadMCU(bin, buf, HuffTables);
        mcus.push_back(mcu);
      }
    }
  }

  void eraseFF00AndSplitRST() {
    std::vector<char> tmp;
    for (int i = 0; i < binary.size(); i++) {
      if (binary[i] != (char)0xff) {
        tmp.push_back(binary[i]);
        continue;
      }
      if (i + 1 < binary.size() && binary[i + 1] == (char)0x00) {
        tmp.push_back(binary[i]);
        i++;
        continue;
      }
      if (i + 1 < binary.size() &&
          13 * 16 <= ((unsigned int)binary[i + 1] % 256) &&
          ((unsigned int)binary[i + 1] % 256) <= 13 * 16 + 7) {
        i++;
        bins.push_back(tmp);
        tmp.clear();
        continue;
      }
    }
    bins.push_back(tmp);
  }

 public:
  void setTable(std::vector<DHTTable> &tables) { HuffTables = tables; }
  void setSegment(SOF &sofSeg, SOS &sosSeg) {
    sof = sofSeg;
    sos = sosSeg;
  }

  void ReadImageData(std::ifstream &ifs) {
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
    eraseFF00AndSplitRST();
    readMCU();
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
