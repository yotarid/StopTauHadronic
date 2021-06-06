#include "../include/Input.h"


namespace in {

  Input::Input(const std::string& process, const std::string& dataFilePath) 
    :  process_(process), dataFile_(dataFilePath), dataFilePath_(dataFilePath)
  {
    LOG(INFO) << BOLDYELLOW << " Data file path : " << WHITE << dataFilePath << RESET;
  }

  Input::~Input(){}

  std::ifstream& Input::GetDataFile(void){ return dataFile_; }

  std::string Input::GetDataFilePath(void){ return dataFilePath_; }

  TFile* Input::GetInputFile(void){ return inFile_; }

  std::string Input::GetInputFilePath(void){ return inFilePath_; }

  TTree* Input::GetRecoTree(void){ return recoTree_; }

  int Input::GetRecoNEvents(void){ return recoNEvents_; }

  TTree* Input::GetGenTree(void){ return genTree_; }

  int Input::GetGenNEvents(void){ return genNEvents_; }

  void Input::InitialiseInput(const std::string& inFilePath)
  {
    //Input data TFile
    LOG(INFO) << BOLDBLUE << "\t Opening input file : " << WHITE << inFilePath << RESET;
    inFilePath_ = inFilePath;
    inFile_ = TFile::Open(inFilePath.c_str(), "READ");
    //Input data TTree
    //RECO
    recoTree_ = static_cast<TTree*>(inFile_->Get("miniaodsim2custom/reco"));
    //GEN
    genTree_ = static_cast<TTree*>(inFile_->Get("miniaodsim2custom/gen"));

    if(recoTree_)
      recoNEvents_ = recoTree_->GetEntries();
    if(genTree_) 
      genNEvents_ = genTree_->GetEntries();

    //RECO branches
    recoTree_->SetBranchAddress("tau_n_reco", &recoTauN_);
    recoTree_->SetBranchAddress("tau_E_reco", &recoTauEVector_);
    recoTree_->SetBranchAddress("tau_px_reco", &recoTauPxVector_);
    recoTree_->SetBranchAddress("tau_py_reco", &recoTauPyVector_);
    recoTree_->SetBranchAddress("tau_pz_reco", &recoTauPzVector_);
    recoTree_->SetBranchAddress("tau_dxy_reco", &recoTaudXYVector_);
    recoTree_->SetBranchAddress("tau_dz_reco", &recoTaudZVector_);
    //DeepTau vs Jets
    recoTree_->SetBranchAddress("tau_byVVVLooseDeepTau2017v2p1VSjet_reco", &recoTauVVVLooseDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byVVLooseDeepTau2017v2p1VSjet_reco", &recoTauVVLooseDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSjet_reco", &recoTauVLooseDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSjet_reco", &recoTauLooseDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSjet_reco", &recoTauMediumDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byTightDeepTau2017v2p1VSjet_reco", &recoTauTightDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byVTightDeepTau2017v2p1VSjet_reco", &recoTauVTightDeepTau2017v2p1VSjetVector_);
    recoTree_->SetBranchAddress("tau_byVVTightDeepTau2017v2p1VSjet_reco", &recoTauVVTightDeepTau2017v2p1VSjetVector_);
    //DeepTau vs Electrons
    recoTree_->SetBranchAddress("tau_VVVLooseDeepTau2017v2p1VSe_reco", &recoTauVVVLooseDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_VVLooseDeepTau2017v2p1VSe_reco", &recoTauVVLooseDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_VLooseDeepTau2017v2p1VSe_reco", &recoTauVLooseDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_LooseDeepTau2017v2p1VSe_reco", &recoTauLooseDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_MediumDeepTau2017v2p1VSe_reco", &recoTauMediumDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_TightDeepTau2017v2p1VSe_reco", &recoTauTightDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_VTightDeepTau2017v2p1VSe_reco", &recoTauVTightDeepTau2017v2p1VSeVector_);
    recoTree_->SetBranchAddress("tau_VVTightDeepTau2017v2p1VSe_reco", &recoTauVVTightDeepTau2017v2p1VSeVector_);
    //DeepTau vs Muons
    recoTree_->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSmu_reco", &recoTauVLooseDeepTau2017v2p1VSmuVector_);
    recoTree_->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSmu_reco", &recoTauLooseDeepTau2017v2p1VSmuVector_);
    recoTree_->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSmu_reco", &recoTauMediumDeepTau2017v2p1VSmuVector_);
    recoTree_->SetBranchAddress("tau_byTightDeepTau2017v2p1VSmu_reco", &recoTauTightDeepTau2017v2p1VSmuVector_);
    //
    recoTree_->SetBranchAddress("tau_decayMode_reco", &recoTauDecayModeVector_);
    recoTree_->SetBranchAddress("METFixEE2017_E_reco", &recoMETE_);
    recoTree_->SetBranchAddress("METFixEE2017_phi_reco", &recoMETPhi_);
    //GEN container
    genTree_->SetBranchAddress("tau_vis_n_gen", &genTauVisN_);
    genTree_->SetBranchAddress("tau_E_gen", &genTauEVector_);
    genTree_->SetBranchAddress("tau_px_gen", &genTauPxVector_);
    genTree_->SetBranchAddress("tau_py_gen", &genTauPyVector_);
    genTree_->SetBranchAddress("tau_pz_gen", &genTauPzVector_);
    genTree_->SetBranchAddress("tau_vis_E_gen", &genTauVisEVector_);
    genTree_->SetBranchAddress("tau_vis_px_gen", &genTauVisPxVector_);
    genTree_->SetBranchAddress("tau_vis_py_gen", &genTauVisPyVector_);
    genTree_->SetBranchAddress("tau_vis_pz_gen", &genTauVisPzVector_);
    genTree_->SetBranchAddress("METFixEE2017_E_gen", &genMETE_);
    genTree_->SetBranchAddress("METFixEE2017_phi_gen", &genMETPhi_);

    isInputInitialised_ = true;
  }

  void Input::FinaliseInput(void)
  {
    LOG(INFO) << BOLDMAGENTA << "\t Closing input file : " << WHITE << inFilePath_ << RESET;
    LOG(INFO) << " " << RESET;
    inFile_->Close();
    isInputInitialised_ = false;
  }

  bool Input::LoadNewEvent(int iEvent)
  {
    if(iEvent % 10000 == 0) LOG(INFO) << BOLDBLUE << "\t\t\t Loading Event : " << +iEvent << RESET;
    return (recoTree_->GetEntry(iEvent) != -1) && (genTree_->GetEntry(iEvent) != -1);
  }

  /*************/
  /* RECO Taus */
  /*************/
  int Input::GetRecoTauN(){ return recoTauN_; }

  double Input::GetRecoTauE(int iTau){ return recoTauEVector_->at(iTau); }

  double Input::GetRecoTauPx(int iTau){ return recoTauPxVector_->at(iTau); }

  double Input::GetRecoTauPy(int iTau){ return recoTauPyVector_->at(iTau); }

  double Input::GetRecoTauPz(int iTau){ return recoTauPzVector_->at(iTau); }

  double Input::GetRecoTaudXY(int iTau){ return recoTaudXYVector_->at(iTau); }

  double Input::GetRecoTaudZ(int iTau){ return recoTaudZVector_->at(iTau); }

  double Input::GetRecoTauDecayMode(int iTau){ return recoTauDecayModeVector_->at(iTau); }

  bool Input::IsRecoTauDeepIDvsEl(int iTau, const std::string& deepTauIDwp)
  {
    switch(tauIDwpMap_[deepTauIDwp])
    {
      case 0 : return recoTauVVVLooseDeepTau2017v2p1VSeVector_->at(iTau) == 1; break;
      case 1 : return recoTauVVLooseDeepTau2017v2p1VSeVector_->at(iTau) == 1; break; 
      case 2 : return recoTauVLooseDeepTau2017v2p1VSeVector_->at(iTau) == 1; break; 
      case 3 : return recoTauLooseDeepTau2017v2p1VSeVector_->at(iTau) == 1; break; 
      case 4 : return recoTauMediumDeepTau2017v2p1VSeVector_->at(iTau) == 1; break;
      case 5 : return recoTauTightDeepTau2017v2p1VSeVector_->at(iTau) == 1; break;
      case 6 : return recoTauVTightDeepTau2017v2p1VSeVector_->at(iTau) == 1; break;
      case 7 : return recoTauVVTightDeepTau2017v2p1VSeVector_->at(iTau) == 1; break;
      default : throw std::runtime_error("Deep Tau ID vs Electron not defined");
    }
  }

  bool Input::IsRecoTauDeepIDvsJet(int iTau, const std::string& deepTauIDwp)
  {
    switch(tauIDwpMap_[deepTauIDwp])
    {
      case 0 : return recoTauVVVLooseDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break;
      case 1 : return recoTauVVLooseDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break; 
      case 2 : return recoTauVLooseDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break; 
      case 3 : return recoTauLooseDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break; 
      case 4 : return recoTauMediumDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break;
      case 5 : return recoTauTightDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break;
      case 6 : return recoTauVTightDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break;
      case 7 : return recoTauVVTightDeepTau2017v2p1VSjetVector_->at(iTau) == 1; break;
      default : throw std::runtime_error("Deep Tau ID vs Jet not defined");
    }
  }

  bool Input::IsRecoTauDeepIDvsMu(int iTau, const std::string& deepTauIDwp)
  {
    switch(tauIDwpMap_[deepTauIDwp])
    {
      case 2 : return recoTauVLooseDeepTau2017v2p1VSmuVector_->at(iTau) == 1; break; 
      case 3  : return recoTauLooseDeepTau2017v2p1VSmuVector_->at(iTau) == 1; break; 
      case 4 : return recoTauMediumDeepTau2017v2p1VSmuVector_->at(iTau) == 1; break;
      case 5  : return recoTauTightDeepTau2017v2p1VSmuVector_->at(iTau) == 1; break;
      default : throw std::runtime_error("Deep Tau ID vs Muon not defined");
    }
  }

  double Input::GetRecoMETE(void){ return recoMETE_; }
  double Input::GetRecoMETPhi(void){ return recoMETPhi_; }


  CLHEP::HepLorentzVector Input::GetRecoTau4Mom(int iTau)
  {
    CLHEP::HepLorentzVector recoTau4Mom;
    recoTau4Mom.setT(fabs(GetRecoTauE(iTau)));
    recoTau4Mom.setX(GetRecoTauPx(iTau));
    recoTau4Mom.setY(GetRecoTauPy(iTau));
    recoTau4Mom.setZ(GetRecoTauPz(iTau));
    return recoTau4Mom;
  }


  std::vector<int> Input::GetRecoTauSelected(const conf::SelCuts& cuts)
  {
    std::vector<int> recoTauSelected;
    for(int iTau = 0; iTau < recoTauN_; iTau++)
    {
      CLHEP::HepLorentzVector recoTau4Mom = GetRecoTau4Mom(iTau);

      if(! (recoTau4Mom.perp() > cuts.tauPt)
            && (fabs(recoTau4Mom.eta()) < cuts.tauEta)
            && (fabs(GetRecoTaudZ(iTau)) < cuts.taudZ)
            && (IsRecoTauDeepIDvsEl(iTau, "Tight"))
            && (IsRecoTauDeepIDvsMu(iTau, "Tight"))
            && (IsRecoTauDeepIDvsJet(iTau, "Tight"))
      ) continue;

      recoTauSelected.push_back(iTau);
    }
    return std::move(recoTauSelected);
  }

  std::pair<int, int> Input::GetRecoTauPair(const conf::SelCuts& cuts, const std::vector<int>& recoTauSelected)
  {      
    std::pair<int, int> tauPair(-1, -1);
    double tauPairHT = 0;
    for(auto iTau1 : recoTauSelected)
    {
      for(auto iTau2 : recoTauSelected)
      {
        if(iTau1 == iTau2) continue;
        //Tau1
        CLHEP::HepLorentzVector  tau1;
        tau1.setT(fabs(GetRecoTauE(iTau1)));
        tau1.setX(GetRecoTauPx(iTau1));
        tau1.setY(GetRecoTauPy(iTau1));
        tau1.setZ(GetRecoTauPz(iTau1));
        //Tau2
        CLHEP::HepLorentzVector  tau2;
        tau2.setT(fabs(GetRecoTauE(iTau2)));
        tau2.setX(GetRecoTauPx(iTau2));
        tau2.setY(GetRecoTauPy(iTau2));
        tau2.setZ(GetRecoTauPz(iTau2));

        if( tau1.perp() < tau2.perp()
            || GetRecoTauE(iTau1)*GetRecoTauE(iTau2) > 0
            || tau1.deltaR(tau2) < cuts.taudeltaR
          ) continue;
        
        double tauPairNewHT = tau1.perp() + tau2.perp();
        if(tauPairNewHT > tauPairHT)
        {            
          tauPairHT = tauPairNewHT;
          tauPair = std::make_pair(iTau1, iTau2);
        }
      }
    }
    return std::move(tauPair);
  }

  double Input::GetRecoTauPairHT(const std::pair<int, int>& tauPair)
  {
    CLHEP::HepLorentzVector tau1 = GetRecoTau4Mom(tauPair.first);
    CLHEP::HepLorentzVector tau2 = GetRecoTau4Mom(tauPair.second);
    return tau1.perp() + tau2.perp();
  }

  double Input::GetRecoTauPairmT2(const std::pair<int, int>& tauPair)
  {
    CLHEP::HepLorentzVector tau1 = GetRecoTau4Mom(tauPair.first);
    CLHEP::HepLorentzVector tau2 = GetRecoTau4Mom(tauPair.second);

    double tauPairmT2 = asymm_mt2_lester_bisect::get_mT2(tau1.m(), tau1.px(), tau1.py(),
                                                      tau2.m(), tau2.px(), tau2.py(),
                                                      GetRecoMETE()*cos(GetRecoMETPhi()), GetRecoMETE()*sin(GetRecoMETPhi()),
                                                      0,0);

    return tauPairmT2;
  }

  /************/
  /* GEN Taus */
  /************/
  int Input::GetGenTauVisN(void){ return genTauVisN_; }

  double Input::GetGenTauVisE(int iTau){ return genTauVisEVector_->at(iTau); }

  double Input::GetGenTauVisPx(int iTau){ return genTauVisPxVector_->at(iTau); }

  double Input::GetGenTauVisPy(int iTau){ return genTauVisPyVector_->at(iTau); }
  
  double Input::GetGenTauVisPz(int iTau){ return genTauVisPzVector_->at(iTau); }

  double Input::GetGenTauE(int iTau){ return genTauEVector_->at(iTau); }

  double Input::GetGenTauPx(int iTau){ return genTauPxVector_->at(iTau); }

  double Input::GetGenTauPy(int iTau){ return genTauPyVector_->at(iTau); }
  
  double Input::GetGenTauPz(int iTau){ return genTauPzVector_->at(iTau); }

  double Input::GetGenMETE(void){ return genMETE_; }

  double Input::GetGenMETPhi(void){ return genMETPhi_; }

}//namespace files
