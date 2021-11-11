#ifndef TAU_H
#define TAU_H

#include "Object.h"

#include <string>
#include <map>
#include <memory>
#include <vector>

namespace obj {
  
  class Tau : public Object {
    public : 
    

      explicit Tau(){};
      ~Tau(){};

      void SetDecayMode(double decayMode){ 
        decayMode_ = decayMode; 
      };

      void SetIsDeepTauIDvsEl(int deepTauIDwpID, bool isDeepTauIDvsEl);

      void SetIsDeepTauIDvsJet(int deepTauIDwpID, bool isDeepTauIDvsJet);

      void SetIsDeepTauIDvsMu(int deepTauIDwpID, bool isDeepTauIDvsMu);

      void SetIsPrompt(bool isPrompt){
        isPrompt_ = isPrompt;
      }

      double GetDecayMode(void){ 
        return decayMode_; 
      };

      bool IsDeepTauIDvsEl(int deepTauIDwpID);
      
      bool IsDeepTauIDvsJet(int deepTauIDwpID);

      bool IsDeepTauIDvsMu(int deepTauIDwpID);

      bool IsPrompt(void){
        return isPrompt_;
      }

    private : 
      //
      double decayMode_;
      //
      bool isVVVLooseDeepTauIDvsEl_;
      bool isVVLooseDeepTauIDvsEl_;
      bool isVLooseDeepTauIDvsEl_;
      bool isLooseDeepTauIDvsEl_;
      bool isMediumDeepTauIDvsEl_;
      bool isTightDeepTauIDvsEl_;
      bool isVTightDeepTauIDvsEl_;
      //
      bool isVVVLooseDeepTauIDvsJet_;
      bool isVVLooseDeepTauIDvsJet_;
      bool isVLooseDeepTauIDvsJet_;
      bool isLooseDeepTauIDvsJet_;
      bool isMediumDeepTauIDvsJet_;
      bool isTightDeepTauIDvsJet_;
      bool isVTightDeepTauIDvsJet_;
      bool isVVTightDeepTauIDvsJet_;
      //
      bool isVLooseDeepTauIDvsMu_;
      bool isLooseDeepTauIDvsMu_;
      bool isMediumDeepTauIDvsMu_;
      bool isTightDeepTauIDvsMu_;
      //
      bool isPrompt_;
  };

  struct TauPair {
    std::shared_ptr<Tau> leadTau;
    std::shared_ptr<Tau> subleadTau;
    std::string deepTauIDwp;
    bool isGenMatched = false;
  };
}

typedef std::vector<std::shared_ptr<obj::Tau>> TauVector;

#endif