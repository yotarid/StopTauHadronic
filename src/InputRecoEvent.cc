#include "../include/InputRecoEvent.h"

namespace in {
  InputRecoEvent::InputRecoEvent(){}

  InputRecoEvent::~InputRecoEvent(){}

  InputRecoEvent& InputRecoEvent::operator=(InputRecoEvent&& other)
  {
    if(tree_)
    {
      delete tree_;
    }
    tree_ = other.tree_;
    other.tree_ = nullptr;
    return *this;
  }

  bool InputRecoEvent::Initialise(TTree* tree)
  {
    if(tree == nullptr) throw std::runtime_error(std::string("ERROR : Input RECO tree is nullptr"));

    tree->SetBranchAddress("tau_n_reco", &tauN_);
    tree->SetBranchAddress("tau_E_reco", &tauEVector_);
    tree->SetBranchAddress("tau_px_reco", &tauPxVector_);
    tree->SetBranchAddress("tau_py_reco", &tauPyVector_);
    tree->SetBranchAddress("tau_pz_reco", &tauPzVector_);
    tree->SetBranchAddress("tau_dxy_reco", &taudXYVector_);
    tree->SetBranchAddress("tau_dz_reco", &taudZVector_);
    //DeepTau vs Jets
    tree->SetBranchAddress("tau_byVVVLooseDeepTau2017v2p1VSjet_reco", &tauVVVLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVVLooseDeepTau2017v2p1VSjet_reco", &tauVVLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSjet_reco", &tauVLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSjet_reco", &tauLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSjet_reco", &tauMediumDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byTightDeepTau2017v2p1VSjet_reco", &tauTightDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVTightDeepTau2017v2p1VSjet_reco", &tauVTightDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVVTightDeepTau2017v2p1VSjet_reco", &tauVVTightDeepTau2017v2p1VSjetVector_);
    //DeepTau vs Electrons
    tree->SetBranchAddress("tau_VVVLooseDeepTau2017v2p1VSe_reco", &tauVVVLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_VVLooseDeepTau2017v2p1VSe_reco", &tauVVLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_VLooseDeepTau2017v2p1VSe_reco", &tauVLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_LooseDeepTau2017v2p1VSe_reco", &tauLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_MediumDeepTau2017v2p1VSe_reco", &tauMediumDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_TightDeepTau2017v2p1VSe_reco", &tauTightDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_VTightDeepTau2017v2p1VSe_reco", &tauVTightDeepTau2017v2p1VSeVector_);
    // tree->SetBranchAddress("tau_VVTightDeepTau2017v2p1VSe_reco", &tauVVTightDeepTau2017v2p1VSeVector_);
    //DeepTau vs Muons
    tree->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSmu_reco", &tauVLooseDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSmu_reco", &tauLooseDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSmu_reco", &tauMediumDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_byTightDeepTau2017v2p1VSmu_reco", &tauTightDeepTau2017v2p1VSmuVector_);
    //
    tree->SetBranchAddress("tau_decayMode_reco", &tauDecayModeVector_); 
    tree->SetBranchAddress("METFixEE2017_E_reco", &METE_);
    tree->SetBranchAddress("METFixEE2017_phi_reco", &METPhi_);

    LOG(INFO) << BOLDBLUE << "\tInitialised input event " << RESET;
    tree_ = tree;
    isInitialised_ = true;

    return isInitialised_;
  }

  bool InputRecoEvent::LoadNewEvent(int iEvent)
  {
    if(iEvent % 10000 == 0) LOG(INFO) << BOLDBLUE << "\t\t\tProcessing Event : " << +iEvent << RESET;
    if( tree_->GetEntry(iEvent) == -1){
      return false;
    }else{
      LoadTaus();
      eventN_ = iEvent;
      return true;  
    }
  }

  void InputRecoEvent::LoadTaus(void)
  {
    //Load Tau objetcs
    taus_.clear();
    for(int iTau = 0; iTau < tauN_; iTau++)
    {
      if(tauN_ < 1) break;
      std::unique_ptr<obj::Tau> tau = std::make_unique<obj::Tau>();

      tau->SetId(iTau);
      //set kinematics
      tau->SetE(tauEVector_->at(iTau));
      tau->SetpX(tauPxVector_->at(iTau));
      tau->SetpY(tauPyVector_->at(iTau));
      tau->SetpZ(tauPzVector_->at(iTau));
      tau->SetdXY(taudXYVector_->at(iTau));
      tau->SetdZ(taudZVector_->at(iTau));

      //set decay mode
      tau->SetDecayMode(tauDecayModeVector_->at(iTau));

      //set DeepTau ID vs El
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["VVVLoose"], tauVVVLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["VVLoose"], tauVVLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["VLoose"], tauVLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["Loose"], tauLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["Medium"], tauMediumDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["Tight"], tauTightDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(tauIDwpMap_["VTight"], tauVTightDeepTau2017v2p1VSeVector_->at(iTau));

      //set DeepTau ID vs Jet
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["VVVLoose"], tauVVVLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["VVLoose"], tauVVLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["VLoose"], tauVLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["Loose"], tauLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["Medium"], tauMediumDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["Tight"], tauTightDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["VTight"], tauVTightDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(tauIDwpMap_["VVTight"], tauVVTightDeepTau2017v2p1VSjetVector_->at(iTau));

      //set DeepTau ID vs Mu
      tau->SetIsDeepTauIDvsMu(tauIDwpMap_["VLoose"], tauVLooseDeepTau2017v2p1VSmuVector_->at(iTau));
      tau->SetIsDeepTauIDvsMu(tauIDwpMap_["Loose"], tauLooseDeepTau2017v2p1VSmuVector_->at(iTau));
      tau->SetIsDeepTauIDvsMu(tauIDwpMap_["Medium"], tauMediumDeepTau2017v2p1VSmuVector_->at(iTau));
      tau->SetIsDeepTauIDvsMu(tauIDwpMap_["Tight"], tauTightDeepTau2017v2p1VSmuVector_->at(iTau));
 
      //push back
      taus_.push_back(std::move(tau));
    }
  }

  TauVector InputRecoEvent::GetSelectedTaus(const conf::SelCuts& cuts)
  {
    // auto start = std::chrono::system_clock::now();
    std::vector<std::unique_ptr<obj::Tau>> selectedTaus;
    // LOG(INFO) << BOLDWHITE << "Taus size : " << taus_.size() << RESET;
    for(auto&& tau : taus_)
    {
      if(tau == nullptr) continue;
      if( (tau->Get4Momentum().perp() < cuts.tauPt)
          || (fabs(tau->Get4Momentum().eta() > cuts.tauEta))
          || (fabs(tau->GetdZ() > cuts.taudZ))
          || (tau->IsDeepTauIDvsEl(tauIDwpMap_[cuts.deepTauID]) == false)
          || (tau->IsDeepTauIDvsMu(tauIDwpMap_[cuts.deepTauID]) == false)
          || (tau->IsDeepTauIDvsJet(tauIDwpMap_[cuts.deepTauID]) == false)
      ) continue;
      selectedTaus.push_back(std::move(tau));
    }
    // auto end = std::chrono::system_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // LOG(INFO) << BOLDYELLOW << "GetSelectedTaus loop : " << +elapsed.count() << " us" << RESET;
    return std::move(selectedTaus);
  }

  obj::TauPair InputRecoEvent::GetSelectedTauPair(const conf::SelCuts& cuts)
  {
    // auto start = std::chrono::system_clock::now();
    TauVector selectedTaus = GetSelectedTaus(cuts);
    // auto end = std::chrono::system_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // LOG(INFO) << BOLDYELLOW << "GetSelectedTaus : " << +elapsed.count() << " us" << RESET;
    // LOG(INFO) << BOLDWHITE << "Selected Taus size : " << selectedTaus.size() << RESET;

    // start = std::chrono::system_clock::now();
    obj::TauPair tauPair;
    double tauPairHT = 0;
    for(auto&& tau1 : selectedTaus)
    {
      for(auto&& tau2 : selectedTaus)
      {
        if(tau1 == tau2) continue;
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
          // auto start = std::chrono::system_clock::now();
          tauPair.leadTau = std::move(tau1);
          tauPair.subleadTau = std::move(tau2);
          // auto end = std::chrono::system_clock::now();
          // auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
          // LOG(INFO) << BOLDYELLOW << "GetSelectedTauPair make pair : " << +elapsed.count() << " us" << RESET;
        }
      }
    }
    // end = std::chrono::system_clock::now();
    // elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // LOG(INFO) << BOLDYELLOW << "GetSelectedTauPair loop : " << +elapsed.count() << " us" << RESET;
    return std::move(tauPair);
  }

  double InputRecoEvent::GetmT2(CLHEP::HepLorentzVector fourMom1, CLHEP::HepLorentzVector fourMom2)
  {
    double mT2 = asymm_mt2_lester_bisect::get_mT2(fourMom1.m(), fourMom1.px(), fourMom1.py(),
                                                  fourMom2.m(), fourMom2.px(), fourMom2.py(),
                                                  METE_*cos(METPhi_), METE_*sin(METPhi_),
                                                  0,0);
    return mT2;
  }

  double InputRecoEvent::GetHT(const std::vector<CLHEP::HepLorentzVector>& listFourMom)
  {
    double HT = 0;
    for(auto fourMom : listFourMom)
      HT += fourMom.perp();
    return HT; 
  }

}