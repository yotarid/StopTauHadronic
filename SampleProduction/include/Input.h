#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

namespace in {
  class Input {
    public : 
      explicit Input(const std::string& inFilePath);
      ~Input() {}

      TFile* GetFile();
      std::string GetFilePath();
      
      TTree* GetRecoTree();
      int GetRecoNEvents();

      TTree* GetGenTree();
      int GetGenNEvents();

      void InitializeEvent();
      void LoadNewEvent(int iEvent);

      /*************/
      /* RECO Taus */
      /*************/
      int GetTauNReco();
      double GetTauEReco(int iTau);
      double GetTauPxReco(int iTau);
      double GetTauPyReco(int iTau);
      double GetTauPzReco(int iTau);
      double GetTaudXYReco(int iTau);
      double GetTaudZReco(int iTau);

      bool IsTauDeepIDvsElReco(int iTau, const std::string& deepTauIDwp);
      bool IsTauDeepIDvsJetReco(int iTau, const std::string& deepTauIDwp);
      bool IsTauDeepIDvsMuReco(int iTau, const std::string& deepTauIDwp);

      double GetMETEReco();
      double GetMETPhiReco();

      /************/
      /* GEN Taus */
      /************/
      int GetTauVisNGen();
      double GetTauVisEGen(int iTau);
      double GetTauVisPxGen(int iTau);
      double GetTauVisPyGen(int iTau);
      double GetTauVisPzGen(int iTau);

      double GetTauEGen(int iTau);
      double GetTauPxGen(int iTau);
      double GetTauPyGen(int iTau);
      double GetTauPzGen(int iTau);

      double GetMETEGen();
      double GetMETPhiGen();


    private :
      TFile* inFile_;
      std::string inFilePath_;

      TTree *recoTree_, *genTree_;
      int recoNEvents_, genNEvents_;

      bool isEventInitialised_ = false;
      //Number of reconstructed taus
      int tauNReco_ = 0;
      //Tau containers
      std::vector <double>
                  // Tau Energy and Kinematics
                  *tauERecoVector_ = nullptr, 
                  *tauPxRecoVector_ = nullptr, *tauPyRecoVector_ = nullptr, *tauPzRecoVector_ = nullptr,
                  *taudXYRecoVector_ = nullptr, *taudZRecoVector_ = nullptr,
                  //Deep Tau Id
                  //Tau Vs Jet
                  *tauVVVLooseDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauVVLooseDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauVLooseDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauLooseDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauMediumDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauTightDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauVTightDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  *tauVVTightDeepTau2017v2p1VSjetRecoVector_ = nullptr,
                  //Tau Vs Electron
                  *tauVVVLooseDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauVVLooseDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauVLooseDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauLooseDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauMediumDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauTightDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauVTightDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  *tauVVTightDeepTau2017v2p1VSeRecoVector_ = nullptr,
                  //Tau Vs Muon 
                  *tauVLooseDeepTau2017v2p1VSmuRecoVector_ = nullptr,
                  *tauLooseDeepTau2017v2p1VSmuRecoVector_ = nullptr,
                  *tauMediumDeepTau2017v2p1VSmuRecoVector_ = nullptr,
                  *tauTightDeepTau2017v2p1VSmuRecoVector_ = nullptr,
                  //Tau Decay Mode 
                  *tauDecayModeRecoVector_ = nullptr;
      //Missing Transverse Energy
      double  METEReco_ = 0 , METPhiReco_ = 0;

      //Tau GEN variables
      //Number of visible generated taus
      int tauVisNGen_ = 0;
      //Tau containers
      std::vector <double>
                  *tauEGenVector_ = nullptr, 
                  *tauPxGenVector_ = nullptr, *tauPyGenVector_ = nullptr, *tauPzGenVector_ = nullptr, 
                  *tauVisEGenVector_ = nullptr, 
                  *tauVisPxGenVector_ = nullptr, *tauVisPyGenVector_ = nullptr, *tauVisPzGenVector_ = nullptr;
      //Missing Transverse Energy
      double METEGen_ = 0, METPhiGen_ = 0;

      //Tau ID working point map
      std::map<std::string, int> tauIDwpMap_ = {{"VVVLoose", 0}, {"VVLoose", 1}, {"VLoose", 2}, {"Loose", 3}, {"Medium", 4}, {"Tight", 5}, {"VTight", 6}, {"VVTight", 7}};
  };
}//namespace in

#endif
