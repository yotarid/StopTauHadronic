#ifndef CONFIGURATION_H
#define CONFIGRATION_H

#include "../utils/pugixml/src/pugixml.hpp"
#include "../utils/pugixml/src/pugiconfig.hpp"
#include <string>

struct SelCuts {
    float tauPt;
    float tauEta;
    float taudZ;
    float taudXY;
    float taudeltaR; 
    float taudR;
};

namespace conf {

  class Configuration {
    public :
      explicit Configuration(const std::string& confFilePath);
      ~Configuration() {}

      std::string GetFilePath();
      std::string GetInputDirPath();

      float GetCutTauPt();
      float GetCutTauEta();
      float GetTauCutdZ();
      float GetTauCutdXY();
      float GetTauCutdeltaR();
      float GetTauCutTaudR();

    private : 
      std::string confFilePath_;
      std::string inputDirPath_;
      SelCuts selCuts_;
  };

}//namespace configuration

#endif