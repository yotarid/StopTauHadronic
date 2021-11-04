#ifndef INPUT_H
#define INPUT_H

#include "../conf/Configuration.h"

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include "../ev/GlobalEvent.h"

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
#include "../lester_mt2_bisect_mod.h"

namespace in {

  class Input {
    public : 
      explicit Input(const std::string& era, const std::string& process, const std::string& channel, bool isSignal, const std::string& dataFilePath);
      ~Input();

      bool Initialise(const std::string& inFilePath);
      void Finalise(void);
      std::ifstream& GetDataFile(void);
      std::string GetDataFilePath(void);
      TFile* GetInputFile(void);
      std::string GetInputFilePath(void);
      std::shared_ptr<in::GlobalEvent> GetGlobalEvent();

     private :
      std::string era_, process_, channel_;
      std::ifstream dataFile_;
      std::string dataFilePath_;
      bool isSignal_;
      TFile* inFile_;
      std::string inFilePath_;
      std::shared_ptr<in::GlobalEvent> globalEvent_;
      bool isInitialised_;
  };
}//namespace in

#endif
