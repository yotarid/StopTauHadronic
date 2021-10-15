#include "../include/OutputRecoEvent.h"

namespace out {
  OutputRecoEvent::OutputRecoEvent(){}

  OutputRecoEvent::~OutputRecoEvent(){}

  OutputRecoEvent& OutputRecoEvent::operator=(OutputRecoEvent&& other)
  {
    if(tree_)
    {
      delete tree_;
    }
    tree_ = other.tree_;
    other.tree_ = nullptr;
    return *this;
  }

  bool OutputRecoEvent::Initialise(TTree* tree)
  {
    if(tree == nullptr) throw std::runtime_error(std::string("ERROR : Output RECO tree is nullptr"));

    //leading tau
    tree->Branch("leadTau_E", &leadTauE_);
    tree->Branch("leadTau_pX", &leadTauPx_);
    tree->Branch("leadTau_pY", &leadTauPy_);
    tree->Branch("leadTau_pZ", &leadTauPz_);
    tree->Branch("leadTau_pT", &leadTauPt_);
    tree->Branch("leadTau_dXY", &leadTaudXY_);
    tree->Branch("leadTau_dZ", &leadTaudZ_);
    tree->Branch("leadTau_DeepTauIDvsJet", &leadTauDeepTauIDvsEl_);
    tree->Branch("leadTau_DeepTauIDvsEl", &leadTauDeepTauIDvsJet_);
    tree->Branch("leadTau_DeepTauIDvsMu", &leadTauDeepTauIDvsMu_);
    tree->Branch("leadTau_decayMode", &leadTauDecayMode_);
    //suleading tau
    tree->Branch("subleadTau_E", &subleadTauE_);
    tree->Branch("subleadTau_pX", &subleadTauPx_);
    tree->Branch("subleadTau_pY", &subleadTauPy_);
    tree->Branch("subleadTau_pZ", &subleadTauPz_);
    tree->Branch("subleadTau_pT", &subleadTauPt_);
    tree->Branch("subleadTau_dXY", &subleadTaudXY_);
    tree->Branch("subleadTau_dX", &subleadTaudZ_);
    tree->Branch("subleadTau_DeepTauIDvsJet", &subleadTauDeepTauIDvsEl_);
    tree->Branch("subleadTau_DeepTauIDvsEl", &subleadTauDeepTauIDvsJet_);
    tree->Branch("subleadTau_DeepTauIDvsMu", &subleadTauDeepTauIDvsMu_);
    tree->Branch("subleadTau_decayMode", &subleadTauDecayMode_);
    //Ta pairtau
    tree->Branch("MET_E", &METE_);
    tree->Branch("MET_phi", &METPhi_);
    tree->Branch("HT", &HT_);
    tree->Branch("mT2", &mT2_);

    LOG(INFO) << BOLDBLUE << "\tInitialised output event " << RESET;
    tree_ = tree;
    isInitialised_ = true;

    return isInitialised_;
  }

  void OutputRecoEvent::LoadNewEvent(obj::TauPair tauPair, const std::string& deepTauIDwp, double METE, double METPhi)
  {
    leadTauE_ = tauPair.leadTau->GetE();
    leadTauPx_ = tauPair.leadTau->GetpX();
    leadTauPy_ = tauPair.leadTau->GetpY();
    leadTauPz_ = tauPair.leadTau->GetpZ();
    leadTauPt_ = tauPair.leadTau->GetpT();
    leadTaudXY_ = tauPair.leadTau->GetdXY();
    leadTaudZ_ = tauPair.leadTau->GetdZ();
    leadTauDeepTauIDvsEl_ = tauPair.leadTau->IsDeepTauIDvsEl(tauIDwpMap_[deepTauIDwp]);
    leadTauDeepTauIDvsJet_ = tauPair.leadTau->IsDeepTauIDvsJet(tauIDwpMap_[deepTauIDwp]);
    leadTauDeepTauIDvsMu_ = tauPair.leadTau->IsDeepTauIDvsMu(tauIDwpMap_[deepTauIDwp]);
    leadTauDecayMode_ = tauPair.leadTau->GetDecayMode();

    subleadTauE_ = tauPair.subleadTau->GetE();
    subleadTauPx_ = tauPair.subleadTau->GetpX();
    subleadTauPy_ = tauPair.subleadTau->GetpY();
    subleadTauPz_ = tauPair.subleadTau->GetpZ();
    subleadTauPt_ = tauPair.subleadTau->GetpT();
    subleadTaudXY_ = tauPair.subleadTau->GetdXY();
    subleadTaudZ_ = tauPair.subleadTau->GetdZ();
    subleadTauDeepTauIDvsEl_ = tauPair.subleadTau->IsDeepTauIDvsEl(tauIDwpMap_[deepTauIDwp]);
    subleadTauDeepTauIDvsJet_ = tauPair.subleadTau->IsDeepTauIDvsJet(tauIDwpMap_[deepTauIDwp]);
    subleadTauDeepTauIDvsMu_ = tauPair.subleadTau->IsDeepTauIDvsMu(tauIDwpMap_[deepTauIDwp]);
    subleadTauDecayMode_ = tauPair.subleadTau->GetDecayMode();

    METE_ = METE;
    METPhi_ = METPhi;

    tree_->Fill();
  }


}