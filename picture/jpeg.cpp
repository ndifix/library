#ifndef NDIFIX_PICTURE_JPEG
#define NDIFIX_PICTURE_JPEG

#include <fstream>
#include <vector>

#include "Utility.cpp"
#include "jpeg/Segment.cpp"

namespace ndifix {

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
  APP0 app0;
  std::vector<APP1> app1;
  SOF sof;
  std::vector<DQT> dqts;
  std::vector<DHT> dhts;
  SOS sos;
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
      if (marker == App0) {
        app0.set(marker);
        app0.ReadSegment(ifs);
        continue;
      }
      if (marker == App1) {
        APP1 app(marker);
        app.ReadSegment(ifs);
        continue;
      }
      if (marker == Dqt) {
        DQT dqt;
        dqt.set(marker);
        dqt.ReadSegment(ifs);
        dqts.push_back(dqt);
        continue;
      }
      if (marker == Dht) {
        DHT dht;
        dht.set(marker);
        dht.ReadSegment(ifs);
        dhts.push_back(dht);
        continue;
      }
      if (marker == Sof) {
        sof.set(marker);
        sof.ReadSegment(ifs);
        continue;
      }
      if (marker == Sos) {
        sos.set(marker);
        sos.ReadSegment(ifs);
        break;
      }
      Segment seg(marker);
      seg.ReadSegment(ifs);
      std::cout << "Unknown Segment:\t\t";
      seg.ShowData();
      segments.push_back(seg);
    }

    imageData.ReadImageData(ifs);

    ifs.close();
  }
};

}  // namespace ndifix

#endif
