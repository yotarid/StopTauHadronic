#ifndef INGENEVENT_H
#define INGENEVENT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../conf/Configuration.h"
#include "../ev/Event.h"
// #include "../include/Electron.h"
// #include "../include/Muon.h"
// #include "../include/Jet.h"
#include "../obj/Tau.h"

#include <TTree.h>
#include <TBranch.h>

#include <memory>
#include <iostream>
#include <utility>

namespace in {
  class GenEvent : public Event {
    public : 
      explicit GenEvent();

      ~GenEvent();

      GenEvent& operator=(GenEvent&& other);

      bool Initialise(TTree* tree) override;

      void LoadTaus(void) override;
      void LoadVisibleTaus(void);

      TauVector GetVisibleTaus(void){
        return visibleTaus_;
      }

    private :

      double stopMGenParam_;
      double neutralinoMGenParam_;
      int outgoingPartonNGen_;
      double scaleWeight1_;
      double scaleWeight2_;
      double scaleWeight3_;
      double scaleWeight4_;
      double scaleWeight5_;
      double scaleWeight6_;
      double scaleWeight7_;
      double scaleWeight8_;
      double scaleWeight9_;

      std::vector<double>* elIsPromptVector_ = nullptr;
      std::vector<double>* muIsPromptVector_ = nullptr;

      int tauVisN_;
      std::vector<double>* tauVisEVector_ = nullptr;
      std::vector<double>* tauVisPxVector_ = nullptr;
      std::vector<double>* tauVisPyVector_ = nullptr;
      std::vector<double>* tauVisPzVector_ = nullptr;
      std::vector<double>* tauIsPromptVector_ = nullptr;
      TauVector visibleTaus_;

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


  };
}

#endif