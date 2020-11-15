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

class Frame {
 private:
  APP0 app0;
  std::vector<APP1> app1;
  SOF sof;
  std::vector<DQT> dqts;
  std::vector<DHT> dhts;
  SOS sos;
  std::vector<Segment> segments;
  std::vector<ImageData> imageData;

 public:
  Frame() {}
  Frame(std::string path) { ReadFrame(path); }

  void ReadFrame(std::string path) {
    std::ifstream ifs;
    try {
      ifs.open(path, std::ios::in | std::ios::binary);
      ifs.exceptions(std::ios::failbit);
    } catch (const std::exception& e) {
      std::cerr << "file cannot open: " << e.what() << std::endl;
    }

    Marker marker(ifs);

    if (marker.isSOI()) {
      std::cout << "Analysis begin" << std::endl;
    } else {
      std::stringstream message;
      message << "Invalid start marker: " << marker;
      throw std::invalid_argument(message.str());
    }

    while (true) {
      marker.set(ifs);
      if (marker.isEOI()) {
        std::cout << "Analysis end." << std::endl;
        break;
      }
      if (marker.isAPP()) {
        APP1 app;
        switch (marker.get()) {
          case 0xe0:
            app0.ReadSegment(ifs);
            break;
          case 0xe1:
            app.ReadSegment(ifs);
            app1.push_back(app);
            break;
          default:
            Segment seg(marker);
            seg.ReadSegment(ifs);
            std::cout << "Unknown APPSegment:\t\t";
            seg.ShowData();
            segments.push_back(seg);
            break;
        }
        continue;
      }
      if (marker.isDQT()) {
        DQT dqt;
        dqt.ReadSegment(ifs);
        dqts.push_back(dqt);
        continue;
      }
      if (marker.isDHT()) {
        DHT dht;
        dht.ReadSegment(ifs);
        dhts.push_back(dht);
        continue;
      }
      if (marker.isSOF()) {
        sof.set(marker);
        sof.ReadSegment(ifs);
        continue;
      }
      if (marker.isSOS()) {
        sos.ReadSegment(ifs);
        ImageData data;
        data.ReadImageData(ifs);
        imageData.push_back(data);
        continue;
      }
      Segment seg(marker);
      seg.ReadSegment(ifs);
      std::cout << "Unknown Segment:\t\t";
      seg.ShowData();
      segments.push_back(seg);
    }

    ifs.close();
  }
};

}  // namespace ndifix

#endif
