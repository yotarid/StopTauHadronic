#include "../include/INRECOEvent.h"

namespace in {
  INRECOEvent::INRECOEvent(){}

  INRECOEvent::~INRECOEvent(){}

  INRECOEvent& INRECOEvent::operator=(INRECOEvent&& other)
  {
    if(tree_)
    {
      delete tree_;
    }
    tree_ = other.tree_;
    other.tree_ = nullptr;
    return *this;
  }

  bool INRECOEvent::Initialise(TTree* tree)
  {
    if(tree == nullptr) throw std::runtime_error(std::string("ERROR : Input RECO tree is nullptr"));

    tree->SetBranchAddress("METFixEE2017_E_reco", &METE_);
    tree->SetBranchAddress("METFixEE2017_phi_reco", &METPhi_);

    //####################### TAU ##########################//
    tree->SetBranchAddress("tau_n_reco", &tauN_);
    tree->SetBranchAddress("tau_E_reco", &tauEVector_);
    tree->SetBranchAddress("tau_px_reco", &tauPxVector_);
    tree->SetBranchAddress("tau_py_reco", &tauPyVector_);
    tree->SetBranchAddress("tau_pz_reco", &tauPzVector_);
    tree->SetBranchAddress("tau_dxy_reco", &taudXYVector_);
    tree->SetBranchAddress("tau_dz_reco", &taudZVector_);
    tree->SetBranchAddress("tau_byVVVLooseDeepTau2017v2p1VSjet_reco", &tauVVVLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVVLooseDeepTau2017v2p1VSjet_reco", &tauVVLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSjet_reco", &tauVLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSjet_reco", &tauLooseDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSjet_reco", &tauMediumDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byTightDeepTau2017v2p1VSjet_reco", &tauTightDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVTightDeepTau2017v2p1VSjet_reco", &tauVTightDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_byVVTightDeepTau2017v2p1VSjet_reco", &tauVVTightDeepTau2017v2p1VSjetVector_);
    tree->SetBranchAddress("tau_VVVLooseDeepTau2017v2p1VSe_reco", &tauVVVLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_VVLooseDeepTau2017v2p1VSe_reco", &tauVVLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_VLooseDeepTau2017v2p1VSe_reco", &tauVLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_LooseDeepTau2017v2p1VSe_reco", &tauLooseDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_MediumDeepTau2017v2p1VSe_reco", &tauMediumDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_TightDeepTau2017v2p1VSe_reco", &tauTightDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_VTightDeepTau2017v2p1VSe_reco", &tauVTightDeepTau2017v2p1VSeVector_);
    tree->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSmu_reco", &tauVLooseDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSmu_reco", &tauLooseDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSmu_reco", &tauMediumDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_byTightDeepTau2017v2p1VSmu_reco", &tauTightDeepTau2017v2p1VSmuVector_);
    tree->SetBranchAddress("tau_decayMode_reco", &tauDecayModeVector_); 

    //####################### JET ##########################//
    tree->SetBranchAddress("jet_n_reco", &jetN_);
    tree->SetBranchAddress("jet_nISR_reco", &jetISRN_);
    tree->SetBranchAddress("jet_E_reco", &jetEVector_);
    tree->SetBranchAddress("jet_px_reco", &jetPxVector_);
    tree->SetBranchAddress("jet_py_reco", &jetPyVector_);
    tree->SetBranchAddress("jet_pz_reco", &jetPzVector_);
    tree->SetBranchAddress("jet_partonFlavour_reco", &jetPartonFlavourVector_);
    tree->SetBranchAddress("jet_hadronFlavour_reco", &jetHadronFlavourVector_);
    tree->SetBranchAddress("jet_isISR_reco", &jetIsISRVector_);
    tree->SetBranchAddress("jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &jetPFCombinedInclusiveSecondaryVertexV2BJetTagsVector_);
    tree->SetBranchAddress("jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &jetLoosePFCombinedInclusiveSecondaryVertexV2BJetTagsVector_);
    tree->SetBranchAddress("jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &jetMediumPFCombinedInclusiveSecondaryVertexV2BJetTagsVector_);
    tree->SetBranchAddress("jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &jetTightPFCombinedInclusiveSecondaryVertexV2BJetTagsVector_);
    tree->SetBranchAddress("jet_pfDeepCSVJetTags_reco", &jetPFDeepCSVJetTagsVector_);
    tree->SetBranchAddress("jet_byLoosePfDeepCSVJetTags_reco", &jetLoosePFDeepCSVJetTagsVector_);
    tree->SetBranchAddress("jet_byMediumPfDeepCSVJetTags_reco", &jetMediumPFDeepCSVJetTagsVector_);
    tree->SetBranchAddress("jet_byTightPfDeepCSVJetTags_reco", &jetTightPFDeepCSVJetTagsVector_);
    tree->SetBranchAddress("jet_pfDeepFlavourJetTags_reco", &jetPFDeepFlavourJetTagsVector_);
    tree->SetBranchAddress("jet_byLoosePfDeepFlavourJetTags_reco", &jetLoosePFDeepFlavourJetTagsVector_);
    tree->SetBranchAddress("jet_byMediumPfDeepFlavourJetTags_reco", &jetMediumPFDeepFlavourJetTagsVector_);
    tree->SetBranchAddress("jet_byTightPfDeepFlavourJetTags_reco", &jetTightPFDeepFlavourJetTagsVector_);
    tree->SetBranchAddress("jet_JECcorr_reco", &jetJECCorrVector_);
    tree->SetBranchAddress("jet_JECcorrUp_reco", &jetJECCorrUpVector_);
    tree->SetBranchAddress("jet_JECcorrDown_reco", &jetJECCorrDownVector_);
    tree->SetBranchAddress("jet_JERcorr_reco", &jetJERCorrVector_);
    tree->SetBranchAddress("jet_JERcorrUp_reco", &jetJERCorrUpVector_);
    tree->SetBranchAddress("jet_JERcorrDown_reco", &jetJERCorrDownVector_);
    tree->SetBranchAddress("jet_JECcorr_reco", &jetJECCorr1Vector_);
    tree->SetBranchAddress("jet_JECcorr_reco", &jetJECCorr2Vector_);
    tree->SetBranchAddress("jet_JECcorr_reco", &jetJECCorr3Vector_);
    tree->SetBranchAddress("jet_JECcorr_reco", &jetJECCorr4Vector_);


    LOG(INFO) << BOLDBLUE << "\tInitialised input event " << RESET;
    tree_ = tree;
    isInitialised_ = true;

    return isInitialised_;
  }

  bool INRECOEvent::LoadNewEvent(int iEvent)
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

  void INRECOEvent::LoadTaus(void)
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
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["VVVLoose"], tauVVVLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["VVLoose"], tauVVLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["VLoose"], tauVLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["Loose"], tauLooseDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["Medium"], tauMediumDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["Tight"], tauTightDeepTau2017v2p1VSeVector_->at(iTau));
      tau->SetIsDeepTauIDvsEl(deepIDwpMap_["VTight"], tauVTightDeepTau2017v2p1VSeVector_->at(iTau));

      //set DeepTau ID vs Jet
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["VVVLoose"], tauVVVLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["VVLoose"], tauVVLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["VLoose"], tauVLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["Loose"], tauLooseDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["Medium"], tauMediumDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["Tight"], tauTightDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["VTight"], tauVTightDeepTau2017v2p1VSjetVector_->at(iTau));
      tau->SetIsDeepTauIDvsJet(deepIDwpMap_["VVTight"], tauVVTightDeepTau2017v2p1VSjetVector_->at(iTau));

      //set DeepTau ID vs Mu
      tau->SetIsDeepTauIDvsMu(deepIDwpMap_["VLoose"], tauVLooseDeepTau2017v2p1VSmuVector_->at(iTau));
      tau->SetIsDeepTauIDvsMu(deepIDwpMap_["Loose"], tauLooseDeepTau2017v2p1VSmuVector_->at(iTau));
      tau->SetIsDeepTauIDvsMu(deepIDwpMap_["Medium"], tauMediumDeepTau2017v2p1VSmuVector_->at(iTau));
      tau->SetIsDeepTauIDvsMu(deepIDwpMap_["Tight"], tauTightDeepTau2017v2p1VSmuVector_->at(iTau));
 
      //push back
      taus_.push_back(std::move(tau));
    }
  }

  TauVector INRECOEvent::GetSelectedTaus(const conf::SelCuts& cuts)
  {
    std::vector<std::unique_ptr<obj::Tau>> selectedTaus;
    for(auto&& tau : taus_)
    {
      if(tau == nullptr) continue;
      if( (tau->Get4Momentum().perp() < cuts.tauPt)
          || (fabs(tau->Get4Momentum().eta() > cuts.tauEta))
          || (fabs(tau->GetdZ() > cuts.taudZ))
          || (tau->IsDeepTauIDvsEl(deepIDwpMap_[cuts.deepTauID]) == false)
          || (tau->IsDeepTauIDvsMu(deepIDwpMap_[cuts.deepTauID]) == false)
          || (tau->IsDeepTauIDvsJet(deepIDwpMap_[cuts.deepTauID]) == false)
      ) continue;
      selectedTaus.push_back(std::move(tau));
    }
    return std::move(selectedTaus);
  }

  obj::TauPair INRECOEvent::GetSelectedTauPair(const conf::SelCuts& cuts)
  {
    TauVector selectedTaus = GetSelectedTaus(cuts);
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

  double INRECOEvent::GetmT2(CLHEP::HepLorentzVector fourMom1, CLHEP::HepLorentzVector fourMom2)
  {
    double mT2 = asymm_mt2_lester_bisect::get_mT2(fourMom1.m(), fourMom1.px(), fourMom1.py(),
                                                  fourMom2.m(), fourMom2.px(), fourMom2.py(),
                                                  METE_*cos(METPhi_), METE_*sin(METPhi_),
                                                  0,0);
    return mT2;
  }

  double INRECOEvent::GetHT(const std::vector<CLHEP::HepLorentzVector>& listFourMom)
  {
    double HT = 0;
    for(auto fourMom : listFourMom)
      HT += fourMom.perp();
    return HT; 
  }
}