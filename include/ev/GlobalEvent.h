#ifndef GLOBALEVENT_H
#define GLOBALEVENT_H

#include "../conf/Configuration.h"

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "RecoEvent.h"
#include "GenEvent.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cmath>

#include <TFile.h>
#include <TTree.h>
#include <TObject.h>
#include <TBranch.h>

namespace in {
  class GlobalEvent {
    public : 

      explicit GlobalEvent();
      ~GlobalEvent();
      GlobalEvent& operator=(GlobalEvent&& other);
      
      bool Initialise(TFile* file);
      bool IsInitialised(void);
      void Finalise(void);
      std::shared_ptr<in::RecoEvent> GetRecoEvent(void);
      std::shared_ptr<in::GenEvent> GetGenEvent(void);
      bool LoadEvent(int iEvent);
      obj::TauPair GetTauPair(const conf::SelCuts& cuts);
      bool IsTauPairGenMatched(obj::TauPair tauPair, const conf::SelCuts& cuts);

    private :

      bool isInitialised_ = false;
      std::shared_ptr<in::RecoEvent> recoEvent_;
      std::shared_ptr<in::GenEvent> genEvent_;
  };
}
#endif