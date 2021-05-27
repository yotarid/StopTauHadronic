#include "../include/Configuration.h"

namespace conf {

  Configuration::Configuration(const std::string& confFilePath) : confFilePath_(confFilePath)
  {}

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