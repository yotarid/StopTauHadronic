#include "../include/ev/GlobalEvent.h"


namespace in {
  GlobalEvent::GlobalEvent(){}

  GlobalEvent::~GlobalEvent(){}

  bool GlobalEvent::Initialise(TFile* file)
  {
    recoEvent_ = std::make_shared<in::RecoEvent>();
    TTree* recoTree = static_cast<TTree*>(file->Get("miniaodsim2custom/reco"));

    genEvent_ = std::make_shared<in::GenEvent>();
    TTree* genTree = static_cast<TTree*>(file->Get("miniaodsim2custom/gen"));

    isInitialised_ = recoEvent_->Initialise(recoTree) & genEvent_->Initialise(genTree);
    return isInitialised_;
  }

  bool GlobalEvent::IsInitialised(void)
  {
    return isInitialised_;
  }

  std::shared_ptr<in::RecoEvent> GlobalEvent::GetRecoEvent()
  {
    return recoEvent_;
  }

  std::shared_ptr<in::GenEvent> GlobalEvent::GetGenEvent()
  {
    return genEvent_;
  }

  bool GlobalEvent::LoadEvent(int iEvent)
  {
    if(iEvent % 10000 == 0) LOG(INFO) << BOLDBLUE << "\t\t\t Loading event : " << +iEvent << RESET;
    return recoEvent_->LoadEvent(iEvent) && genEvent_->LoadEvent(iEvent);
  }

  obj::TauPair GlobalEvent::GetTauPair(const conf::SelCuts& cuts) 
  {
    TauVector selectedRecoTaus = recoEvent_->GetSelectedTaus(cuts);
    //
    obj::TauPair tauPair;
    double tauPairHT = 0;
    for(auto&& recoTau1 : selectedRecoTaus)
    {
      for(auto&& recoTau2 : selectedRecoTaus)
      {
        //avoid reprocessing same tau
        if(recoTau1 == recoTau2 || recoTau1 == nullptr || recoTau2 == nullptr) continue;

        //Check if reco tau passes selection criteria 
        CLHEP::HepLorentzVector recoTau1FourMom = recoTau1->Get4Momentum();
        CLHEP::HepLorentzVector recoTau2FourMom = recoTau2->Get4Momentum();
        //
        if( (recoTau1->GetpT() < recoTau2->GetpT())
            || (recoTau1->GetE() * recoTau2->GetE() > 0)
            || (recoTau1FourMom.deltaR(recoTau2FourMom) < cuts.taudeltaR)
        ) continue;

        double tauPairNewHT = recoTau1->GetpT() + recoTau2->GetpT();
        if(tauPairNewHT > tauPairHT)
        {
          tauPairHT = tauPairNewHT;
          tauPair.leadTau = recoTau1;
          tauPair.subleadTau = recoTau2;
          tauPair.deepTauIDwp = cuts.deepTauID;
        }
      }
    }
    if(IsTauPairGenMatched(tauPair, cuts)) tauPair.isGenMatched = true;
    return tauPair;
  }
     
  bool GlobalEvent::IsTauPairGenMatched(obj::TauPair tauPair, const conf::SelCuts& cuts)
  {
    if((tauPair.leadTau == nullptr) || (tauPair.subleadTau == nullptr)) return false;
    TauVector visibleGenTaus = genEvent_->GetVisibleTaus();
    //two iterations to gen match each tau from the pair
    for(int iTau = 0; iTau < 2; iTau++)
    {
      std::shared_ptr<obj::Tau> recoTau = (iTau == 0) ? tauPair.leadTau : tauPair.subleadTau;
      double minDeltaR = 999;
      int genMatchTauId = -1;
      for(auto&& genTau : visibleGenTaus)
      {
        if((genTau->IsPrompt() == false)
            || (genTau->GetpT() < cuts.tauPt)
            || (genTau->GetEta() > cuts.tauEta)
            || (genTau->IsUsedToGenMatch() == true)
        ) continue;

        double deltaR = recoTau->Get4Momentum().deltaR(genTau->Get4Momentum());
        if(deltaR < minDeltaR)
        {
          minDeltaR = deltaR;
          genMatchTauId = genTau->GetId();
        }
      }
      if(genMatchTauId >= 0)
      {
        if(minDeltaR < cuts.taudeltaR)
        {
          recoTau->SetIsGenMatched(true);
          visibleGenTaus[genMatchTauId]->SetIsUsedToGenMatch(true);
        }
      }
    }
    return (tauPair.leadTau->IsGenMatched() && tauPair.subleadTau->IsGenMatched());
  }
}