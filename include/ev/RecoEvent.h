#ifndef INPUTRECOEVENT_H
#define INPUTRECOEVENT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../conf/Configuration.h"
#include "Event.h"
// #include "../include/Electron.h"
// #include "../include/Muon.h"
// #include "../include/Jet.h"
#include "../obj/Tau.h"

#include <TTree.h>
#include <TBranch.h>

#include "../lester_mt2_bisect_mod.h"

#include <memory>
#include <iostream>
#include <utility>

#include <chrono>

namespace in {

  class RecoEvent : public Event {
    public:

      explicit RecoEvent();
      ~RecoEvent();
      RecoEvent& operator=(RecoEvent&& other);

      bool Initialise(TTree* tree) override;
      bool LoadEvent(int iEvent) override;
      void LoadTaus(void) override;
      void LoadJets(void) override;
      // void LoadElectrons(void) override {}
      // void LoadMuons(void) override {}

      TauVector GetSelectedTaus(const conf::SelCuts& cuts);
      double GetmT2(CLHEP::HepLorentzVector fourMom1, CLHEP::HepLorentzVector fourMom2);
      double GetHT(const std::vector<CLHEP::HepLorentzVector>& listFourMom);

    private:

      //######################################################//
      //####################### TAU ##########################//
      //######################################################//
      std::vector<double>* taudXYVector_ = nullptr;
      std::vector<double>* taudZVector_ = nullptr;
      std::vector<double>* tauVVVLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVVLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauLooseDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauMediumDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauTightDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVTightDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVVTightDeepTau2017v2p1VSjetVector_ = nullptr;
      std::vector<double>* tauVVVLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVVLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauLooseDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauMediumDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauTightDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVTightDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVVTightDeepTau2017v2p1VSeVector_ = nullptr;
      std::vector<double>* tauVLooseDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauLooseDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauMediumDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauTightDeepTau2017v2p1VSmuVector_ = nullptr;
      std::vector<double>* tauDecayModeVector_ = nullptr;


      //######################################################//
      //####################### JET ##########################//
      //######################################################//
      int jetISRN_;
      std::vector<double>* jetPartonFlavourVector_ = nullptr;
      std::vector<double>* jetHadronFlavourVector_ = nullptr;
      std::vector<double>* jetIsISRVector_ = nullptr;
      std::vector<double>* jetPFCombinedInclusiveSecondaryVertexV2BJetTagsVector_ = nullptr;
      std::vector<double>* jetLoosePFCombinedInclusiveSecondaryVertexV2BJetTagsVector_ = nullptr;
      std::vector<double>* jetMediumPFCombinedInclusiveSecondaryVertexV2BJetTagsVector_ = nullptr;
      std::vector<double>* jetTightPFCombinedInclusiveSecondaryVertexV2BJetTagsVector_ = nullptr;
      std::vector<double>* jetPFDeepCSVJetTagsVector_ = nullptr;
      std::vector<double>* jetLoosePFDeepCSVJetTagsVector_ = nullptr;
      std::vector<double>* jetMediumPFDeepCSVJetTagsVector_ = nullptr;
      std::vector<double>* jetTightPFDeepCSVJetTagsVector_ = nullptr;
      std::vector<double>* jetPFDeepFlavourJetTagsVector_ = nullptr;
      std::vector<double>* jetLoosePFDeepFlavourJetTagsVector_ = nullptr;
      std::vector<double>* jetMediumPFDeepFlavourJetTagsVector_ = nullptr;
      std::vector<double>* jetTightPFDeepFlavourJetTagsVector_ = nullptr;
      std::vector<double>* jetJECCorrVector_ = nullptr;
      std::vector<double>* jetJECCorrUpVector_ = nullptr;
      std::vector<double>* jetJECCorrDownVector_ = nullptr;
      std::vector<double>* jetJERCorrVector_ = nullptr;
      std::vector<double>* jetJERCorrUpVector_ = nullptr;
      std::vector<double>* jetJERCorrDownVector_ = nullptr;
      std::vector<double>* jetJECCorr1Vector_ = nullptr;
      std::vector<double>* jetJECCorr2Vector_ = nullptr;
      std::vector<double>* jetJECCorr3Vector_ = nullptr;
      std::vector<double>* jetJECCorr4Vector_ = nullptr;


      //######################################################//
      //##################### ELECTRON #######################//
      //######################################################//
      std::vector<double>* elEVector_ = nullptr;
      std::vector<double>* elPxVector_ = nullptr;
      std::vector<double>* elPyVector_ = nullptr;
      std::vector<double>* elPzVector_ = nullptr;
      std::vector<double>* eldXYVector_ = nullptr;
      std::vector<double>* eldZVector_ = nullptr;
      

      std::map<std::string, int> wpMap_ = {{"VVVLoose", 0}, 
                                           {"VVLoose", 1}, 
                                           {"VLoose", 2}, 
                                           {"Loose", 3}, 
                                           {"Medium", 4}, 
                                           {"Tight", 5}, 
                                           {"VTight", 6}, 
                                           {"VVTight", 7}};
 

  };
}

#endif