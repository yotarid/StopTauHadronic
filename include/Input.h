#ifndef INPUT_H
#define INPUT_H

#include "Configuration.h"

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

#include <CLHEP/Vector/LorentzVector.h>
#include "lester_mt2_bisect_mod.h"

namespace in {

  class Input {
    public : 
      explicit Input(const std::string& era, const std::string& process, const std::string& channel, bool isSignal, const std::string& dataFilePath);
      ~Input();

      bool Initialise(const std::string& inFilePath);

      void Finalise(void);

      std::ifstream& GetDataFile(void){ 
        return dataFile_; 
      }

      std::string GetDataFilePath(void){ 
        return dataFilePath_; 
      }
    
      TFile* GetInputFile(void){ 
        return inFile_; 
      }

      std::string GetInputFilePath(void){ 
        return inFilePath_; 
      }

      int GetRECOEventN(void){
        return recoEventN_;
      }

      int GetGENEventN(void){
        return genEventN_;
      }

      std::shared_ptr<in::RecoEvent> GetRECOEvent(int iEvent);

      std::shared_ptr<in::GenEvent> GetGENEvent(int iEvent);

     private :

      std::string era_, process_, channel_;
      std::ifstream dataFile_;
      std::string dataFilePath_;
      bool isSignal_;

      TFile* inFile_;
      std::string inFilePath_;

      std::shared_ptr<in::RecoEvent> recoEvent_;
      int recoEventN_;

      std::shared_ptr<in::GenEvent> genEvent_;
      int genEventN_;

      bool isInitialised_;
  };
}//namespace in

#endif
