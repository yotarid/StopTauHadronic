#ifndef OUTPUT_H
#define OUTPUT_H

#include "../extern/easylogging/easylogging++.h"
#include "../extern/easylogging/consolecolor.h"

#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <cstdlib>

#include "OUTEvent.h"

#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TBranch.h"

namespace out {
  class Output {
    public : 
      explicit Output(const std::string& era, const std::string& process, const std::string& channel);
      ~Output();

      bool Initialise(const std::string& outFileName);

      void Finalise(void);

      TFile* GetOutputFile(void){
        return outFile_;
      }

      std::string GetOutputFilePath(void){
        return outFilePath_;
      }

      std::shared_ptr<out::OUTEvent> GetEvent(void){
        return event_;
      }

    private :
      std::string era_, process_, channel_;

      TFile* outFile_;
      TDirectory* outROOTDir_;
      std::string outFilePath_;

      bool isInitialised_;

      std::shared_ptr<out::OUTEvent> event_;
  };
}//namespace out

#endif
