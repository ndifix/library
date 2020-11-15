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

  void ReadSegment(std::ifstream& ifs) {
    char f, s;
    ifs.get(f);
    ifs.get(s);
    length = GetInt(f, s);

    param.resize(length - 2);
    for (auto& i : param) ifs.get(i);
  }

  void ShowData() {
    std::cout << "marker: ";
    marker.print();
    std::cout << std::hex << "\tlength: " << std::setfill('0') << std::right
              << std::setw(4) << length << std::dec << std::endl;
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
  APP0() { marker = App0; }

  void ReadSegment(std::ifstream& ifs) {
    std::cout << "APP0\t"
              << "JPEG File Interchange Format (JFIF)" << std::endl;
    Segment::ReadSegment(ifs);
    char id[5] = {param[0], param[1], param[2], param[3], param[4]};
    if (id == "JFIF") ID = "JFIF";
    setVer(param[5], param[6]);
    U = GetInt(0, param[7]);
    Xd = GetInt(param[8], param[9]);
    Yd = GetInt(param[10], param[11]);
    Xt = GetInt(0, param[12]);
    Yt = GetInt(0, param[13]);
    thumb.resize(Xt, Yt);
    /*
    read thumbnail
    */

    if (DebugMode) ShowData();
  }

  void ShowData() {
    Segment::ShowData();
    std::cout << "Ver: " << Ver << std::endl;
    std::cout << "U =\t" << U << (U == 1 ? ": inch" : ": cm") << std::endl;
    std::cout << "Xd=\t" << Xd << std::endl;
    std::cout << "Yd=\t" << Yd << std::endl;
    std::cout << "Xt=\t" << Xt << std::endl;
    std::cout << "Yt=\t" << Yt << std::endl;
    std::cout << std::endl;
  }
};

class APP1 : public Segment {
 public:
  APP1() { marker = App1; }

  void ReadSegment(std::ifstream& ifs) {
    std::cout << "APP1\t"
              << "Exchangeable Image File Format (Exif)" << std::endl;
    Segment::ReadSegment(ifs);

    if (DebugMode) ShowData();
  }

  void ShowData() {
    Segment::ShowData();
    std::cout << std::endl;
  }
};

class DQTTable {
 private:
  char pt;
  std::vector<std::vector<int>> Q =
      std::vector<std::vector<int>>(8, std::vector<int>(8));

 public:
  DQTTable() {}

  void ReadQuantizationTable(std::vector<char>::iterator& itr) {
    pt = *itr;
    itr++;
    for (int i = 0; i < 64; i++) {
      if ((unsigned int)pt & 0xf0) {
        char f, s;
        f = *itr;
        itr++;
        s = *itr;
        itr++;
        Q[i / 8][i % 8] = GetInt(f, s);
      } else {
        char f;
        f = *itr;
        itr++;
        Q[i / 8][i % 8] = GetInt(0, f);
      }
    }
  }

  void ShowTable() {
    std::cout << "Quantization Table\t";
    PrintHex(pt);
    std::cout << std::endl;

    for (int i = 0; i < 64; i++) {
      std::cout << Q[i / 8][i % 8];
      if (i % 8 == 7)
        std::cout << std::endl;
      else
        std::cout << " ";
    }
    std::cout << std::endl;
  }
};

class DQT : public Segment {
 private:
  std::vector<DQTTable> tables;

 public:
  DQT() { marker = Dqt; }

  void ReadSegment(std::ifstream& ifs) {
    std::cout << "DQT\t\t"
              << "Define Quantization Table" << std::endl;
    Segment::ReadSegment(ifs);

    auto begin = param.begin();
    while (begin != param.end()) {
      DQTTable dqtTable;
      dqtTable.ReadQuantizationTable(begin);
      tables.push_back(dqtTable);
    }

    if (DebugMode) ShowData();
  }

  void ShowData() {
    Segment::ShowData();
    for (auto table : tables) table.ShowTable();
  }
};

class DHTTable {
 private:
  // table class
  int Tc;
  // huffman table destination identifier
  int Th;
  // length of huffman codes
  std::vector<int> L = std::vector<int>(16);
  // value associated with Huffman code
  std::vector<std::vector<char>> V = std::vector<std::vector<char>>(16);

 public:
  void ReadHuffmanTable(std::vector<char>::iterator& itr) {
    Tc = GetInt(0, *itr) / 16;
    Th = GetInt(0, *itr) % 16;
    itr++;
    for (int i = 0; i < 16; i++) {
      L[i] = GetInt(0, *itr);
      V[i].resize(L[i]);
      itr++;
    }
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < L[i]; j++) {
        V[i][j] = GetInt(0, *itr);
        itr++;
      }
    }
  }

  void ShowTable() {
    std::cout << "Tc=\t" << Tc << (Tc == 0 ? ": 8bit" : ": 16bit") << std::endl;
    std::cout << "Th=\t" << Th << std::endl;
    std::cout << "Huffman Table" << std::endl;
    for (int i = 0; i < 16; i++) {
      std::cout << i << ":\t";
      for (int j = 0; j < L[i]; j++) {
        PrintHex(V[i][j]);
        std::cout << "\t";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};

class DHT : public Segment {
 private:
  std::vector<DHTTable> tables;

 public:
  DHT() { marker = Dht; }

  void ReadSegment(std::ifstream& ifs) {
    std::cout << "DHT\t\t"
              << "Define Huffman Table" << std::endl;
    Segment::ReadSegment(ifs);
    auto begin = param.begin();
    while (begin != param.end()) {
      DHTTable dhtTable;
      dhtTable.ReadHuffmanTable(begin);
      tables.push_back(dhtTable);
    }

    if (DebugMode) ShowData();
  }

  void ShowData() {
    Segment::ShowData();
    for (auto table : tables) table.ShowTable();
  }
};

class SOF : public Segment {
 private:
  // precision
  int P;
  // image size
  int X, Y;
  // Number of image components in frame
  int Nf;

  // component id
  std::vector<int> C;
  // sampling factor (horizontal / vertical)
  std::vector<int> H, V;
  // quantization table destination selector
  std::vector<int> Tq;

  std::string CtoColor(int c) {
    switch (c) {
      case 1:
        return "Y ";
      case 2:
        return "Cb";
      case 3:
        return "Cr";
      case 4:
        return "I ";
      case 5:
        return "Q ";
      default:
        return "  ";
    }
  }

 public:
  SOF() { marker = Sof; }

  void ReadSegment(std::ifstream& ifs) {
    std::cout << "SOF\t\t"
              << "Baseline DCT Process Frame" << std::endl;
    Segment::ReadSegment(ifs);
    P = GetInt(0, param[0]);
    Y = GetInt(param[1], param[2]);
    X = GetInt(param[3], param[4]);
    Nf = GetInt(0, param[5]);

    C.resize(Nf);
    H.resize(Nf);
    V.resize(Nf);
    Tq.resize(Nf);

    int index = 6;
    for (int i = 0; i < Nf; i++) {
      C[i] = GetInt(0, param[index]);
      index++;
      H[i] = GetInt(0, param[index]) / 16;
      V[i] = GetInt(0, param[index]) % 16;
      index++;
      Tq[i] = GetInt(0, param[index]);
      index++;
    }

    if (DebugMode) ShowData();
  }

  void ShowData() {
    Segment::ShowData();
    std::cout << "P =\t" << P << std::endl;
    std::cout << "Y =\t" << Y << std::endl;
    std::cout << "X =\t" << X << std::endl;
    std::cout << "Nf=\t" << Nf << "\t\t";
    if (Nf == 1) std::cout << "grayscale" << std::endl;
    if (Nf == 3) std::cout << "YCbCr or YIQ" << std::endl;
    if (Nf == 4) std::cout << "CMYK" << std::endl;
    std::cout << "  \tH\tV\tTq" << std::endl;
    for (int i = 0; i < Nf; i++) {
      std::cout << CtoColor(C[i]) << "\t" << H[i] << "\t" << V[i] << "\t"
                << Tq[i] << std::endl;
    }
    std::cout << std::endl;
  }
};

class SOS : public Segment {
 private:
  // number of image components in scan
  int Ns;
  // scan component selector
  std::vector<int> C;
  // DC table destination selector
  std::vector<int> Td;
  // AC table destination selector
  std::vector<int> Ta;
  // start/end of spectral selection
  int Ss, Se;
  // successive approximation bit position high/low
  int Ah, Al;

 public:
  SOS() { marker = Sos; }

  void ReadSegment(std::ifstream& ifs) {
    std::cout << "SOS\t\t"
              << "Start of Scan" << std::endl;
    Segment::ReadSegment(ifs);

    Ns = GetInt(0, param[0]);
    C = Td = Ta = std::vector<int>(Ns);
    int index = 1;
    for (int i = 0; i < Ns; i++) {
      C[i] = GetInt(0, param[index]);
      index++;
      Td[i] = GetInt(0, param[index]) / 16;
      Ta[i] = GetInt(0, param[index]) % 16;
      index++;
    }

    Ss = GetInt(0, param[index]);
    index++;
    Se = GetInt(0, param[index]);
    index++;
    Ah = GetInt(0, param[index]) / 16;
    Al = GetInt(0, param[index]) % 16;

    if (DebugMode) ShowData();
  }

  void ShowData() {
    Segment::ShowData();
    std::cout << "Ns=\t" << Ns << std::endl;
    std::cout << "C \tTd\tTa" << std::endl;
    for (int i = 0; i < Ns; i++) {
      std::cout << C[i] << "\t\t" << Td[i] << "\t\t" << Ta[i] << std::endl;
    }
    std::cout << "Ss=\t" << Ss << std::endl;
    std::cout << "Se=\t" << Se << std::endl;
    std::cout << "Ah=\t" << Ah << std::endl;
    std::cout << "Al=\t" << Al << std::endl;
    std::cout << std::endl;
  }
};

}  // namespace ndifix

#endif
