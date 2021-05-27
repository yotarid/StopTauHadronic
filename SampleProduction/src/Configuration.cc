#include "../include/Configuration.h"

namespace conf {

  Configuration::Configuration(const std::string& confFilePath, const std::string& era) 
    : confFilePath_(confFilePath), era_(era)
  {
    if(confFilePath.find(".xml") != std::string::npos)
      ParseSettings(confFilePath);
    else
      throw std::runtime_error("ERROR : settings file is not XML");
  }

  void Configuration::ParseSettings(const std::string& confFilePath)
  {
    pugi::xml_document confFile;
    pugi::xml_parse_result result = confFile.load_file(confFilePath.c_str());
    if(!result)
      throw std::runtime_error("ERROR : couldn't open " + confFilePath);

    for(pugi::xml_node eraNode = confFile.child("RunDescription").child("Era"); eraNode; eraNode = eraNode.next_sibling())
    {
      if(eraNode.attribute("date").value() == era_)
      {
        
      }
    }
  }

  std::string Configuration::GetFilePath(){ return confFilePath_; }

  VecStr Configuration::GetInputDirList(const std::string& process){ return inputDirMap_[process]; }

  std::string Configuration::GetOutputFilePath(const std::string& process){ return outFileMap_[process]; }

  VecStr Configuration::GetProcessList(){ return processList_; }

  float Configuration::GetCutTauPt(const std::string& process){ return selCutsMap_[process].tauPt; }

  float Configuration::GetCutTauEta(const std::string& process){ return selCutsMap_[process].tauEta; }

  float Configuration::GetTauCutdZ(const std::string& process){ return selCutsMap_[process].taudZ; }

  float Configuration::GetTauCutdXY(const std::string& process){ return selCutsMap_[process].taudXY; }

  float Configuration::GetTauCutdeltaR(const std::string& process){ return selCutsMap_[process].taudeltaR; }

  float Configuration::GetTauCutTaudR(const std::string& process){ return selCutsMap_[process].taudR; }

}//namespace configuration