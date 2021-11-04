#include "../include/conf/Configuration.h"

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
          std::string processName = processNode.attribute("name").value();
          bool isSignal = ( std::string(processNode.attribute("isSignal").value()) == "true" ) ? true : false;
          LOG(INFO) << BOLDWHITE << "Process isSignal = " << std::boolalpha << isSignal << RESET;
          isSignalMap_.insert(std::make_pair(processName, isSignal));
          ParseFileMap(processName, processNode.child("Data"));
          ParseSelectionCuts(processName, processNode.child("SelectionCuts"));
        }
      }
    }
  }

  void Configuration::ParseFileMap(const std::string& processName, pugi::xml_node dataNode)
  {
    VecStr channelList;
    MapStrToStr channelDataFileMap, channelOutputFileMap;
    for(pugi::xml_node channelNode = dataNode.child("Channel"); channelNode; channelNode = channelNode.next_sibling())
    {
      std::string channelName = channelNode.attribute("name").value();
      channelList.push_back(channelName);
      // 
      std::string dataFile = std::getenv("SAMPLEPRODUCTION_DATA_DIR") + std::string("/") + channelNode.attribute("directory").value() + std::string("/") + channelNode.attribute("file").value();
      channelDataFileMap.insert(std::make_pair(channelName, dataFile));
      //
      std::string outputFile = channelName + "_selected";
      channelOutputFileMap.insert(std::make_pair(channelName, outputFile));
    }
    channelMap_.insert(std::make_pair(processName, channelList));
    dataFileMap_.insert(std::make_pair(processName, channelDataFileMap));
    outFileMap_.insert(std::make_pair(processName, channelOutputFileMap));
  }

  void Configuration::ParseSelectionCuts(const std::string& processName, pugi::xml_node selCutNode)
  {
    SelCuts selCuts;
    for(pugi::xml_node cutNode = selCutNode.child("cut"); cutNode; cutNode = cutNode.next_sibling())
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
        selCuts.deepTauID = cutNode.attribute("deepTauID").value();
      }
    }
    //fill selection cuts map
    selCutsMap_.insert(std::make_pair(processName, selCuts));
  }
}//namespace configuration