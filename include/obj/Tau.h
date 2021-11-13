#ifndef TAU_H
#define TAU_H

#include "Object.h"

namespace obj {
  
  class Tau : public Object {
    public : 
    

      explicit Tau(){};
      ~Tau(){};

      void SetDecayMode(double decayMode){ 
        decayMode_ = decayMode; 
      };

      void SetIsDeepTauIDvsEl(int wpID, bool isDeepTauIDvsEl);

      void SetIsDeepTauIDvsJet(int wpID, bool isDeepTauIDvsJet);

      void SetIsDeepTauIDvsMu(int wpID, bool isDeepTauIDvsMu);

      void SetIsPrompt(bool isPrompt){
        isPrompt_ = isPrompt;
      }

      double GetDecayMode(void){ 
        return decayMode_; 
      };

      bool IsDeepTauIDvsEl(int wpID);
      
      bool IsDeepTauIDvsJet(int wpID);

      bool IsDeepTauIDvsMu(int wpID);

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