#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../utils/pugixml.hpp"
#include "../utils/pugiconfig.hpp"
#include "../utils/easylogging++.h"
#include "../utils/consolecolor.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cstdlib>

struct SelCuts {
    float tauPt;
    float tauEta;
    float taudZ;
    float taudXY;
    float taudeltaR; 
    float taudR;
};

namespace conf {

  typedef std::vector<std::string> VecStr;
  typedef std::map< std::string, VecStr > MapStrToVecStr;
  typedef std::map< std::string, std::string > MapStrToStr;
  typedef std::map< std::string, SelCuts > SelCutsMap;

  class Configuration {
    public :
      explicit Configuration(const std::string& confFilePath, const std::string& era);
      ~Configuration() {}

      void ParseSettings(const std::string& confFilePath);
      void ParseInputFileList(pugi::xml_node processNode);
      void ParseOutputFile(pugi::xml_node processNode);
      void ParseSelectionCuts(pugi::xml_node processNode);

      std::string GetFilePath();
      std::string GetEra();
      VecStr GetProcessList();
      VecStr GetInputFileList(const std::string& process);
      std::string GetOutputFileName(const std::string& process);

      float GetCutTauPt(const std::string& process);
      float GetCutTauEta(const std::string& process);
      float GetCutTaudZ(const std::string& process);
      float GetCutTaudXY(const std::string& process);
      float GetCutTaudeltaR(const std::string& process);
      float GetCutTaudR(const std::string& process);

    private : 
      std::string confFilePath_;
      std::string era_;

      VecStr processList_;
      MapStrToVecStr inputFileMap_;
      MapStrToStr outFileMap_;
      SelCutsMap selCutsMap_;
  };

}//namespace configuration

#endif