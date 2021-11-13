#include "../include/obj/Tau.h"

namespace obj {
  
  void Tau::SetIsDeepTauIDvsEl(int wpID, bool isDeepTauIDvsEl)
  {
    switch(wpID)
    {
      case 0 : isVVVLooseDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      case 1 : isVVLooseDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      case 2 : isVLooseDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      case 3 : isLooseDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      case 4 : isMediumDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      case 5 : isTightDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      case 6 : isVTightDeepTauIDvsEl_ = isDeepTauIDvsEl; break;
      default : throw std::runtime_error("Deep Tau ID vs Electron not defined");
    }
  }

  void Tau::SetIsDeepTauIDvsJet(int wpID, bool isDeepTauIDvsJet)
  {
    switch(wpID)
    {
      case 0 : isVVVLooseDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 1 : isVVLooseDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 2 : isVLooseDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 3 : isLooseDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 4 : isMediumDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 5 : isTightDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 6 : isVTightDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      case 7 : isVVTightDeepTauIDvsJet_ = isDeepTauIDvsJet; break;
      default : throw std::runtime_error("Deep Tau ID vs Jet not defined");
    }
  }

  void Tau::SetIsDeepTauIDvsMu(int wpID, bool isDeepTauIDvsMu)
  {
    switch(wpID)
    {
      case 2 : isVLooseDeepTauIDvsMu_ = isDeepTauIDvsMu; break;
      case 3 : isLooseDeepTauIDvsMu_ = isDeepTauIDvsMu; break;
      case 4 : isMediumDeepTauIDvsMu_ = isDeepTauIDvsMu; break;
      case 5 : isTightDeepTauIDvsMu_ = isDeepTauIDvsMu; break;
      default : throw std::runtime_error("Deep Tau ID vs Muon not defined");
    }
  }

  bool Tau::IsDeepTauIDvsEl(int wpID) 
  {
    switch(wpID)
    {
      case 0 : return isVVVLooseDeepTauIDvsEl_; break;
      case 1 : return isVVLooseDeepTauIDvsEl_; break;
      case 2 : return isVLooseDeepTauIDvsEl_; break;
      case 3 : return isLooseDeepTauIDvsEl_; break;
      case 4 : return isMediumDeepTauIDvsEl_; break;
      case 5 : return isTightDeepTauIDvsEl_; break;
      case 6 : return isVTightDeepTauIDvsEl_; break;
      default : throw std::runtime_error("Deep Tau ID vs Electron not defined");
    }
  }

  bool Tau::IsDeepTauIDvsJet(int wpID) 
  {
    switch(wpID)
    {
      case 0 : return isVVVLooseDeepTauIDvsJet_; break;
      case 1 : return isVVLooseDeepTauIDvsJet_; break;
      case 2 : return isVLooseDeepTauIDvsJet_; break;
      case 3 : return isLooseDeepTauIDvsJet_; break;
      case 4 : return isMediumDeepTauIDvsJet_; break;
      case 5 : return isTightDeepTauIDvsJet_; break;
      case 6 : return isVTightDeepTauIDvsJet_; break;
      case 7 : return isVVTightDeepTauIDvsJet_; break;
      default : throw std::runtime_error("Deep Tau ID vs Jet not defined");
    }
  }

  bool Tau::IsDeepTauIDvsMu(int wpID) 
  {
    switch(wpID)
    {
      case 2 : return isVLooseDeepTauIDvsMu_; break;
      case 3 : return isLooseDeepTauIDvsMu_; break; 
      case 4 : return isMediumDeepTauIDvsMu_; break;
      case 5 : return isTightDeepTauIDvsMu_; break;
      default : throw std::runtime_error("Deep Tau ID vs Muon not defined");
    }
  }
}