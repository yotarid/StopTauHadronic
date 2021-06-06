#ifndef INPUT_H
#define INPUT_H

#include "../utils/easylogging++.h"
#include "../utils/consolecolor.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

namespace in {
  class Input {
    public : 
      explicit Input(const std::string& dataFilePath);
      ~Input();

      TFile* GetInputFile();
      std::string GetInputFilePath();

      std::ifstream& GetDataFile();
      std::string GetDataFilePath();
      
      TTree* GetRecoTree();
      int GetRecoNEvents();

      TTree* GetGenTree();
      int GetGenNEvents();

      void InitialiseInput(const std::string& inFilePath);
      bool LoadNewEvent(int iEvent);
      void FinaliseInput();

      /*************/
      /* RECO Taus */
      /*************/
      int GetRecoTauN();
      double GetRecoTauE(int iTau);
      double GetRecoTauPx(int iTau);
      double GetRecoTauPy(int iTau);
      double GetRecoTauPz(int iTau);
      double GetRecoTaudXY(int iTau);
      double GetRecoTaudZ(int iTau);

      bool IsRecoTauDeepIDvsEl(int iTau, const std::string& deepTauIDwp);
      bool IsRecoTauDeepIDvsJet(int iTau, const std::string& deepTauIDwp);
      bool IsRecoTauDeepIDvsMu(int iTau, const std::string& deepTauIDwp);

      double GetRecoMETE();
      double GetRecoMETPhi();

      /************/
      /* GEN Taus */
      /************/
      int GetGenTauVisN();
      double GetGenTauVisE(int iTau);
      double GetGenTauVisPx(int iTau);
      double GetGenTauVisPy(int iTau);
      double GetGenTauVisPz(int iTau);

      double GetGenTauE(int iTau);
      double GetGenTauPx(int iTau);
      double GetGenTauPy(int iTau);
      double GetGenTauPz(int iTau);

      double GetGenMETE();
      double GetGenMETPhi();


    private :
      std::ifstream dataFile_;
      std::string dataFilePath_;

      TFile* inFile_;
      std::string inFilePath_;

      TTree *recoTree_, *genTree_;
      int recoNEvents_, genNEvents_;

      bool isInputInitialised_ = false;
      //Number of reconstructed taus
      int recoTauN_ = 0;
      //Tau containers
      std::vector <double>
                  // Tau Energy and Kinematics
                  *recoTauEVector_ = nullptr, 
                  *recoTauPxVector_ = nullptr, *recoTauPyVector_ = nullptr, *recoTauPzVector_ = nullptr,
                  *recoTaudXYVector_ = nullptr, *recoTaudZVector_ = nullptr,
                  //Deep Tau Id
                  //Tau Vs Jet
                  *recoTauVVVLooseDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauVVLooseDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauVLooseDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauLooseDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauMediumDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauTightDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauVTightDeepTau2017v2p1VSjetVector_ = nullptr,
                  *recoTauVVTightDeepTau2017v2p1VSjetVector_ = nullptr,
                  //Tau Vs Electron
                  *recoTauVVVLooseDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauVVLooseDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauVLooseDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauLooseDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauMediumDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauTightDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauVTightDeepTau2017v2p1VSeVector_ = nullptr,
                  *recoTauVVTightDeepTau2017v2p1VSeVector_ = nullptr,
                  //Tau Vs Muon 
                  *recoTauVLooseDeepTau2017v2p1VSmuVector_ = nullptr,
                  *recoTauLooseDeepTau2017v2p1VSmuVector_ = nullptr,
                  *recoTauMediumDeepTau2017v2p1VSmuVector_ = nullptr,
                  *recoTauTightDeepTau2017v2p1VSmuVector_ = nullptr,
                  //Tau Decay Mode 
                  *recoTauDecayModeVector_ = nullptr;
      //Missing Transverse Energy
      double  recoMETE_ = 0 , recoMETPhi_ = 0;

      //Tau GEN variables
      //Number of visible generated taus
      int genTauVisN_ = 0;
      //Tau containers
      std::vector <double>
                  *genTauEVector_ = nullptr, 
                  *genTauPxVector_ = nullptr, *genTauPyVector_ = nullptr, *genTauPzVector_ = nullptr, 
                  *genTauVisEVector_ = nullptr, 
                  *genTauVisPxVector_ = nullptr, *genTauVisPyVector_ = nullptr, *genTauVisPzVector_ = nullptr;
      //Missing Transverse Energy
      double genMETE_ = 0, genMETPhi_ = 0;

      //Tau ID working point map
      std::map<std::string, int> tauIDwpMap_ = {{"VVVLoose", 0}, {"VVLoose", 1}, {"VLoose", 2}, {"Loose", 3}, {"Medium", 4}, {"Tight", 5}, {"VTight", 6}, {"VVTight", 7}};
  };
}//namespace in

#endif
