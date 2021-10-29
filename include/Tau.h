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

      void SetId(int id){ id_ = id; }

      void SetDecayMode(double decayMode){ decayMode_ = decayMode; };

      void SetIsDeepTauIDvsEl(int deepTauIDwpID, bool isDeepTauIDvsEl);

      void SetIsDeepTauIDvsJet(int deepTauIDwpID, bool isDeepTauIDvsJet);

      void SetIsDeepTauIDvsMu(int deepTauIDwpID, bool isDeepTauIDvsMu);

      int GetId(){ 
        return id_; 
      }

      double GetDecayMode(void){ 
        return decayMode_; 
      };

      bool IsDeepTauIDvsEl(int deepTauIDwpID);
      
      bool IsDeepTauIDvsJet(int deepTauIDwpID);

      bool IsDeepTauIDvsMu(int deepTauIDwpID);

    private : 

      int id_;
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
  };

  struct TauPair {
    std::unique_ptr<Tau> leadTau;
    std::unique_ptr<Tau> subleadTau;
    std::string deepTauIDwp;
  };
}

#endif