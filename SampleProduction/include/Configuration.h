#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../utils/pugixml/src/pugixml.hpp"
#include "../utils/pugixml/src/pugiconfig.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

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
      void ParseInputDir(pugi::xml_node processNode);
      void ParseOutputFile(pugi::xml_node processNode);
      void ParseSelectionCuts(pugi::xml_node processNode);

      std::string GetFilePath();
      VecStr GetInputDirList(const std::string& process);
      std::string GetOutputFilePath(const std::string& process);

      VecStr GetProcessList();

      float GetCutTauPt(const std::string& process);
      float GetCutTauEta(const std::string& process);
      float GetTauCutdZ(const std::string& process);
      float GetTauCutdXY(const std::string& process);
      float GetTauCutdeltaR(const std::string& process);
      float GetTauCutTaudR(const std::string& process);

    private : 
      std::string confFilePath_;
      std::string era_;

      VecStr processList_;
      MapStrToVecStr inputDirMap_;
      MapStrToStr outFileMap_;
      SelCutsMap selCutsMap_;
  };

}//namespace configuration

#endif