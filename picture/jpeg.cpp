#ifndef NDIFIX_PICTURE_JPEG
#define NDIFIX_PICTURE_JPEG

#include <fstream>
#include <vector>

#include "Utility.cpp"
#include "jpeg/ImageData.cpp"
#include "jpeg/Segment.cpp"

namespace ndifix {

class Frame {
 private:
  APP0 app0;
  std::vector<APP1> app1;
  DRI dri;
  SOF sof;
  std::vector<DQT> dqts;
  std::vector<DHT> dhts;
  std::vector<DHTTable> HuffTable;
  std::vector<DQTTable> QTable;
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
      if (marker.isDRI()) {
        dri.ReadSegment(ifs);
        continue;
      }
      if (marker.isDQT()) {
        DQT dqt;
        dqt.ReadSegment(ifs);
        dqts.push_back(dqt);
        auto table = dqt.getTables();
        for (auto t : table) QTable.push_back(t);
        continue;
      }
      if (marker.isDHT()) {
        DHT dht;
        dht.ReadSegment(ifs);
        dhts.push_back(dht);
        auto table = dht.getTables();
        for (auto t : table) HuffTable.push_back(t);
        continue;
      }
      if (marker.isSOF()) {
        sof.set(marker);
        sof.ReadSegment(ifs);
        if (!marker.isSOF0()) throw std::exception();
        continue;
      }
      if (marker.isSOS()) {
        sos.ReadSegment(ifs);
        imageData.setTable(HuffTable, QTable);
        imageData.setSegment(sof, sos);
        imageData.ReadImageData(ifs);
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
