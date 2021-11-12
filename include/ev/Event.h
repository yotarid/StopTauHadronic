#ifndef EVENT_H
#define EVENT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../conf/Configuration.h"
#include "../obj/Tau.h"

#include <memory>
#include <iostream>
#include <utility>

#include <TTree.h>
#include <TBranch.h>

namespace in {
  class Event {
    public :

      explicit Event();
      ~Event();
      Event& operator=(Event&& other);


      virtual bool Initialise(TTree* tree) = 0;
      virtual void LoadTaus(void) = 0;
      // virtual void LoadJets(void) = 0;
      // virtual void LoadElectrons(void) = 0;
      // virtual void LoadMuons(void) = 0;
      bool IsInitialised(void);
      TTree* GetTree(void);
      int GetEventN(void);
      virtual bool LoadEvent(int iEvent) = 0;

      double GetTauN(void);
      TauVector GetTaus(void);

      double GetMETE(void);
      double GetMETPhi(void);

    protected :
      TTree* tree_;
      int eventN_;

      bool isInitialised_;

      int tauN_;
      std::vector<double>* tauEVector_ = nullptr;
      std::vector<double>* tauPxVector_ = nullptr;
      std::vector<double>* tauPyVector_ = nullptr;
      std::vector<double>* tauPzVector_ = nullptr;
      TauVector taus_;

      int jetN_;
      std::vector<double>* jetEVector_ = nullptr;
      std::vector<double>* jetPxVector_ = nullptr;
      std::vector<double>* jetPyVector_ = nullptr;
      std::vector<double>* jetPzVector_ = nullptr;
      // JetVector jets_;

      int muN_;
      std::vector<double>* muEVector_ = nullptr;
      std::vector<double>* muPxVector_ = nullptr;
      std::vector<double>* muPyVector_ = nullptr;
      std::vector<double>* muPzVector_ = nullptr;
      // MuonVector muons_;

      int elN_;
      std::vector<double>* elEVector_ = nullptr;
      std::vector<double>* elPxVector_ = nullptr;
      std::vector<double>* elPyVector_ = nullptr;
      std::vector<double>* elPzVector_ = nullptr;
      // ElectronVector electrons_;

      double METE_;
      double METPhi_;
  };
}

#endif