#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "../extern/pugixml/pugixml.hpp"
#include "../extern/pugixml/pugiconfig.hpp"
#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cstdlib>



namespace conf {

  struct SelCuts {
      float tauPt;
      float tauEta;
      float taudZ;
      float taudXY;
      float taudeltaR; 
      float taudR;
      std::string deepTauID;
  };

  typedef std::vector<std::string> VecStr;
  typedef std::map< std::string, std::string > MapStrToStr;
  typedef std::map< std::string, VecStr > MapStrToVecStr;
  typedef std::map< std::string, std::map < std::string, std::string > > MapStrToMapStr;
  typedef std::map< std::string, SelCuts > SelCutsMap;

  class Configuration {
    public :
      explicit Configuration(const std::string& confFilePath, const std::string& era);
      ~Configuration() {}

      void ParseSettings(const std::string& confFilePath);
      void ParseFileMap(const std::string& processName, pugi::xml_node dataNode);
      void ParseSelectionCuts(const std::string& processName, pugi::xml_node selCutNode);

      std::string GetFilePath(void);
      std::string GetEra(void);
      VecStr GetProcessList(void);
      VecStr GetChannelList(const std::string& process);
      std::string GetDataFileName(const std::string& process, const std::string& channel);
      std::string GetOutputFileName(const std::string& process, const std::string& channel);

      SelCuts GetSelCuts(const std::string& process);

    private : 
      std::string confFilePath_;
      std::string era_;
      VecStr processList_;
      MapStrToVecStr channelMap_;
      MapStrToMapStr dataFileMap_;
      MapStrToMapStr outFileMap_;
      SelCutsMap selCutsMap_;
  };

}//namespace configuration

#endif