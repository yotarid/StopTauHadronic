#ifndef OUTPUTRECOEVENT_H
#define OUTPUTRECOEVENT_H

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

namespace out {

  class OutputRecoEvent {
    public :
      explicit OutputRecoEvent();

      ~OutputRecoEvent();

      OutputRecoEvent& operator=(OutputRecoEvent&& other);

      bool Initialise(TTree* tree);

      void LoadNewEvent(obj::TauPair tauPair, const std::string& deepTauIDwp, double METE, double METPhi);

      bool IsInitialised(void){ 
        return isInitialised_; 
      }

    private :

      TTree* tree_;

      bool isInitialised_;

      double leadTauE_;
      double leadTauPx_;
      double leadTauPy_;
      double leadTauPz_;
      double leadTauPt_;
      double leadTaudXY_;
      double leadTaudZ_;
      double leadTauDeepTauIDvsEl_;
      double leadTauDeepTauIDvsJet_;
      double leadTauDeepTauIDvsMu_;
      double leadTauDecayMode_;

      double subleadTauE_;
      double subleadTauPx_;
      double subleadTauPy_;
      double subleadTauPz_;
      double subleadTauPt_;
      double subleadTaudXY_;
      double subleadTaudZ_;
      double subleadTauDeepTauIDvsEl_;
      double subleadTauDeepTauIDvsJet_;
      double subleadTauDeepTauIDvsMu_;
      double subleadTauDecayMode_;

      double HT_;
      double METE_;
      double METPhi_;
      double mT2_;

      std::map<std::string, int> tauIDwpMap_ = {{"VVVLoose", 0}, 
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