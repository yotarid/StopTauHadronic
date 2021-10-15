#ifndef INPUTRECOEVENT_H
#define INPUTRECOEVENT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../include/Configuration.h"
// #include "../include/Electron.h"
// #include "../include/Muon.h"
// #include "../include/Jet.h"
#include "../include/Tau.h"

#include <TTree.h>
#include <TBranch.h>

#include "lester_mt2_bisect_mod.h"

#include <memory>
#include <iostream>
#include <utility>

#include <chrono>

typedef std::vector<std::unique_ptr<obj::Tau>> TauVector;

namespace in {

  class InputRecoEvent {
    public:
      explicit InputRecoEvent();

      ~InputRecoEvent();

      InputRecoEvent& operator=(InputRecoEvent&& other);

      bool Initialise(TTree* tree);

      void LoadTaus(void);

      bool IsInitialised(void){ return isInitialised_; };

      TTree* GetTree(void){ return tree_; }

      int GetEventN(void){return eventN_; }

      bool LoadNewEvent(int iEvent);

      TauVector GetTaus(void){ return std::move(taus_); }

      double GetMETE(void){ return METE_; };

      double GetMETPhi(void){ return METPhi_; };

      TauVector GetSelectedTaus(const conf::SelCuts& cuts);

      obj::TauPair GetSelectedTauPair(const conf::SelCuts& cuts);

      double GetmT2(CLHEP::HepLorentzVector fourMom1, CLHEP::HepLorentzVector fourMom2);

      double GetHT(const std::vector<CLHEP::HepLorentzVector>& listFourMom);

      double GetTauN(void){ return tauN_; };

    private:
      TTree* tree_;
      int eventN_;

      int tauN_;
      std::vector<double>* tauEVector_ = nullptr;
      std::vector<double>* tauPxVector_ = nullptr;
      std::vector<double>* tauPyVector_ = nullptr;
      std::vector<double>* tauPzVector_ = nullptr;
      std::vector<double>* taudXYVector_ = nullptr;
      std::vector<double>* taudZVector_ = nullptr;
      //Tau Vs Jet
      std::vector<double>* tauVVVLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVVLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauMediumDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauTightDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVTightDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVVTightDeepTau2017v2p1VSjetVector_ = nullptr;
      //Tau Vs Electron
      std::vector<double>* tauVVVLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVVLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauMediumDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauTightDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVTightDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVVTightDeepTau2017v2p1VSeVector_ = nullptr;
      //Tau Vs Muon 
      std::vector<double>* tauVLooseDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauLooseDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauMediumDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauTightDeepTau2017v2p1VSmuVector_ = nullptr;
      //Tau Decay Mode 
      std::vector<double>* tauDecayModeVector_ = nullptr;

      std::map<std::string, int> tauIDwpMap_ = {{"VVVLoose", 0}, 
                                                {"VVLoose", 1}, 
                                                {"VLoose", 2}, 
                                                {"Loose", 3}, 
                                                {"Medium", 4}, 
                                                {"Tight", 5}, 
                                                {"VTight", 6}, 
                                                {"VVTight", 7}};

      double METE_;
      double METPhi_;

      bool isInitialised_;

      TauVector taus_;
  };
}

#endif