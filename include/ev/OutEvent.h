#ifndef OUTEVENT_H
#define OUTEVENT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../conf/Configuration.h"
// #include "../obj/Electron.h"
// #include "../obj/Muon.h"
// #include "../obj/Jet.h"
#include "../obj/Tau.h"

#include <TTree.h>
#include <TBranch.h>

#include "../lester_mt2_bisect_mod.h"

#include <memory>
#include <iostream>
#include <utility>

#include <chrono>

namespace out {

  class OutEvent {
    public :
      explicit OutEvent();

      ~OutEvent();

      OutEvent& operator=(OutEvent&& other);

      bool Initialise(TTree* tree);

      void LoadNewEvent(obj::TauPair tauPair, double METE, double METPhi, double HT, double mT2);

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

      std::map<std::string, int> deepIDwpMap_ = {{"VVVLoose", 0}, 
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
