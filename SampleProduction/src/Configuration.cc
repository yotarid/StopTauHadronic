#include "../include/Configuration.h"

namespace conf {

  Configuration::Configuration(const std::string& confFilePath) : confFilePath_(confFilePath)
  {}

  std::string Configuration::GetFilePath(){ return confFilePath_; }

  std::string Configuration::GetInputDirPath(){ return inputDirPath_; }

  float Configuration::GetCutTauPt(){ return selCuts_.tauPt; }

  float Configuration::GetCutTauEta(){ return selCuts_.tauEta; }

  float Configuration::GetTauCutdZ(){ return selCuts_.taudZ; }

  float Configuration::GetTauCutdXY(){ return selCuts_.taudXY; }

  float Configuration::GetTauCutdeltaR(){ return selCuts_.taudeltaR; }

  float Configuration::GetTauCutTaudR(){ return selCuts_.taudR; }

}//namespace configuration