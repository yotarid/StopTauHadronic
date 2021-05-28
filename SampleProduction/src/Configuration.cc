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
        for(pugi::xml_node processNode = eraNode.child("Process"); processNode; processNode = processNode.next_sibling())
        {
          ParseInputDir(processNode);
          ParseOutputFile(processNode);
          ParseSelectionCuts(processNode);
        }
        
      }
    }
  }

  void Configuration::ParseInputDir(pugi::xml_node processNode)
  {
    //get process name
    std::string processName = processNode.attribute("name").value();
    //fill process directory list
    VecStr inputDirList;
    for(pugi::xml_node dirNode = processNode.child("Input").child("Directory"); dirNode; dirNode = dirNode.next_sibling())
      inputDirList.push_back(dirNode.attribute("name").value());
  }

  void Configuration::ParseOutputFile(pugi::xml_node processNode)
  {
    //get process name
    std::string processName = processNode.attribute("name").value();
    //get process output file name
    std::string outFileName = processNode.child("Output").attribute("name").value();
  }

  void Configuration::ParseSelectionCuts(pugi::xml_node processNode)
  {
    //get process name
    std::string processName = processNode.attribute("name").value();
    //get selection cuts
    SelCuts selCuts;
    for(pugi::xml_node cutNode = processNode.child("SelectionCuts").child("cut"); cutNode; cutNode = cutNode.next_sibling())
    {
      std::string object = cutNode.attribute("name").value();
      if(object == "tau")
      {
        selCuts.tauPt = cutNode.attribute("pT").as_float(40);
        selCuts.tauEta = cutNode.attribute("eta").as_float(2.1);
        selCuts.taudZ = cutNode.attribute("dZ").as_float(24);
        selCuts.taudXY = cutNode.attribute("dXY").as_float(2);
        selCuts.taudeltaR = cutNode.attribute("deltaR").as_float(0.5);
        selCuts.taudR = cutNode.attribute("dR").as_float(0.5);
      }
    }
    selCutsMap_.insert(std::make_pair(processName, selCuts));
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