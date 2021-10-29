#ifndef INGENEVENT_H
#define INGENEVENT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../include/Configuration.h"
// #include "../include/Electron.h"
// #include "../include/Muon.h"
// #include "../include/Jet.h"
#include "../include/Tau.h"

#include <TTree.h>
#include <TBranch.h>

#include <memory>
#include <iostream>
#include <utility>

typedef std::vector<std::unique_ptr<obj::Tau>> TauVector;

namespace in {
  class GenEvent {
    public : 
      explicit GenEvent();

      ~GenEvent();

      GenEvent& operator=(GenEvent&& other);

      bool Initialise(TTree* tree);

      bool IsInitialised(void){ 
        return isInitialised_; 
      };

      TTree* GetTree(void){ 
        return tree_; 
      }

      int GetEventN(void){
        return eventN_; 
      }

      bool LoadEvent(int iEvent);

      void LoadTaus(void);

    private :
      TTree* tree_;
      int eventN_;

      double stopMGenParam_;
      double neutralinoMGenParam_;
      double outgoingPartonNGen_;
      double scaleWeight1_;
      double scaleWeight2_;
      double scaleWeight3_;
      double scaleWeight4_;
      double scaleWeight5_;
      double scaleWeight6_;
      double scaleWeight7_;
      double scaleWeight8_;
      double scaleWeight9_;

      int elN_;
      std::vector<double>* elEVector_ = nullptr;
      std::vector<double>* elPxVector_ = nullptr;
      std::vector<double>* elPyVector_ = nullptr;
      std::vector<double>* elPzVector_ = nullptr;
      std::vector<double>* elIsPromptVector_ = nullptr;

      int muN_;
      std::vector<double>* muEVector_ = nullptr;
      std::vector<double>* muPxVector_ = nullptr;
      std::vector<double>* muPyVector_ = nullptr;
      std::vector<double>* muPzVector_ = nullptr;
      std::vector<double>* muIsPromptVector_ = nullptr;

      std::vector<double>* tauEVector_ = nullptr;
      std::vector<double>* tauPxVector_ = nullptr;
      std::vector<double>* tauPyVector_ = nullptr;
      std::vector<double>* tauPzVector_ = nullptr;
      std::vector<double>* tauVisNVector_ = nullptr;
      std::vector<double>* tauVisEVector_ = nullptr;
      std::vector<double>* tauVisPxVector_ = nullptr;
      std::vector<double>* tauVisPyVector_ = nullptr;
      std::vector<double>* tauVisPzVector_ = nullptr;
      TauVector taus_;

      int tQuarkN_;
      std::vector<double>* tQuarkEVector_ = nullptr;
      std::vector<double>* tQuarkPxVector_ = nullptr;
      std::vector<double>* tQuarkPyVector_ = nullptr;
      std::vector<double>* tQuarkPzVector_ = nullptr;

      int bQuarkN_;
      std::vector<double>* bQuarkEVector_ = nullptr;
      std::vector<double>* bQuarkPxVector_ = nullptr;
      std::vector<double>* bQuarkPyVector_ = nullptr;
      std::vector<double>* bQuarkPzVector_ = nullptr;

      int wBosonN_;
      std::vector<double>* wBosonEVector_ = nullptr;
      std::vector<double>* wBosonPxVector_ = nullptr;
      std::vector<double>* wBosonPyVector_ = nullptr;
      std::vector<double>* wBosonPzVector_ = nullptr;

      int zBosonN_;
      std::vector<double>* zBosonEVector_ = nullptr;
      std::vector<double>* zBosonPxVector_ = nullptr;
      std::vector<double>* zBosonPyVector_ = nullptr;
      std::vector<double>* zBosonPzVector_ = nullptr;

      int stauN_;
      std::vector<double>* stauEVector_ = nullptr;
      std::vector<double>* stauPxVector_ = nullptr;
      std::vector<double>* stauPyVector_ = nullptr;
      std::vector<double>* stauPzVector_ = nullptr;

      int stopN_;
      std::vector<double>* stopEVector_ = nullptr;
      std::vector<double>* stopPxVector_ = nullptr;
      std::vector<double>* stopPyVector_ = nullptr;
      std::vector<double>* stopPzVector_ = nullptr;

      int charginoN_;
      std::vector<double>* charginoEVector_ = nullptr;
      std::vector<double>* charginoPxVector_ = nullptr;
      std::vector<double>* charginoPyVector_ = nullptr;
      std::vector<double>* charginoPzVector_ = nullptr;

      int jetN_;
      std::vector<double>* jetEVector_ = nullptr;
      std::vector<double>* jetPxVector_ = nullptr;
      std::vector<double>* jetPyVector_ = nullptr;
      std::vector<double>* jetPzVector_ = nullptr;

      double METE_;
      double METPhi_;

      bool isInitialised_;
  };
}

#endif