#include "../include/EventWrapper.h"


namespace in {
  EventWrapper::EventWrapper(){}

  EventWrapper::~EventWrapper(){}

  bool EventWrapper::Initialise(TFile* file)
  {
    recoEvent_ = std::make_shared<in::RecoEvent>();
    TTree* recoTree = static_cast<TTree*>(file->Get("miniaodsim2custom/reco"));

    genEvent_ = std::make_shared<in::GenEvent>();
    TTree* genTree = static_cast<TTree*>(file->Get("miniaodsim2custom/gen"));

    isInitialised_ = recoEvent_->Initialise(recoTree) & genEvent_->Initialise(genTree);
    return isInitialised_;
  }

  bool EventWrapper::IsInitialised(void)
  {
    return isInitialised_;
  }

  std::shared_ptr<in::RecoEvent> EventWrapper::GetRecoEvent()
  {
    return recoEvent_;
  }

  std::shared_ptr<in::GenEvent> EventWrapper::GetGenEvent()
  {
    return genEvent_;
  }


  // template <class T> 
  // std::shared_ptr<T> EventWrapper::GetEvent(const std::string& type)
  // {
  //   if(type == "RECO")
  //   {
  //     return genEvent_;
  //   }
  //   else if(type == "GEN")
  //   {
  //     return recoEvent_; 
  //   }
  //   else
  //   {
  //     throw std::runtime_error("ERROR : EventWrapper::GetEvent : Unkown event type");
  //   }
  // }

  bool EventWrapper::LoadEvent(int iEvent)
  {
    if(iEvent % 10000 == 0) LOG(INFO) << BOLDBLUE << "\t\t\t Loading event : " << +iEvent << RESET;
    return recoEvent_->LoadEvent(iEvent) && genEvent_->LoadEvent(iEvent);
  }

  obj::TauPair EventWrapper::GetTauPair(const conf::SelCuts& cuts) 
  {
    TauVector selectedTaus = recoEvent_->GetSelectedTaus(cuts);
    obj::TauPair tauPair;
    double tauPairHT = 0;
    for(auto&& tau1 : selectedTaus)
    {
      for(auto&& tau2 : selectedTaus)
      {
        if(tau1 == tau2 || tau1 == nullptr || tau2 == nullptr) continue;
        CLHEP::HepLorentzVector tau1FourMom = tau1->Get4Momentum();
        CLHEP::HepLorentzVector tau2FourMom = tau2->Get4Momentum();
        if( (tau1FourMom.perp() < tau2FourMom.perp())
            || (tau1->GetE() * tau2->GetE() > 0)
            || (tau1FourMom.deltaR(tau2FourMom) < cuts.taudeltaR)
        ) continue;
        double tauPairNewHT = tau1FourMom.perp() + tau2FourMom.perp();
        if(tauPairNewHT > tauPairHT)
        {
          tauPairHT = tauPairNewHT;
          tauPair.leadTau = std::move(tau1);
          tauPair.subleadTau = std::move(tau2);
          tauPair.deepTauIDwp = cuts.deepTauID;
        }
      }
    }
    return std::move(tauPair);
  }



}