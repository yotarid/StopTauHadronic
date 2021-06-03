#include "../include/Input.h"


namespace in {

  Input::Input(const std::string& dataFilePath) :  dataFile_(dataFilePath), dataFilePath_(dataFilePath)
  {
    std::cout << "Using file " << dataFilePath << std::endl;
  }

  Input::~Input(){}

  std::ifstream& Input::GetDataFile(){ return dataFile_; }

  std::string Input::GetDataFilePath(){ return dataFilePath_; }

  TFile* Input::GetInputFile(){ return inFile_; }

  std::string Input::GetInputFilePath(){ return inFilePath_; }

  TTree* Input::GetRecoTree(){ return recoTree_; }

  int Input::GetRecoNEvents(){ return recoNEvents_; }

  TTree* Input::GetGenTree(){ return genTree_; }

  int Input::GetGenNEvents(){ return genNEvents_; }

  void Input::InitialiseInput(const std::string& inFilePath)
  {
    //Input data TFile
    std::cout << "Opening file " << inFilePath << std::endl;
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
    recoTree_->SetBranchAddress("tau_n_reco", &tauNReco_);
    recoTree_->SetBranchAddress("tau_E_reco", &tauERecoVector_);
    recoTree_->SetBranchAddress("tau_px_reco", &tauPxRecoVector_);
    recoTree_->SetBranchAddress("tau_py_reco", &tauPyRecoVector_);
    recoTree_->SetBranchAddress("tau_pz_reco", &tauPzRecoVector_);
    recoTree_->SetBranchAddress("tau_dxy_reco", &taudXYRecoVector_);
    recoTree_->SetBranchAddress("tau_dz_reco", &taudZRecoVector_);
    //DeepTau vs Jets
    recoTree_->SetBranchAddress("tau_byVVVLooseDeepTau2017v2p1VSjet_reco", &tauVVVLooseDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byVVLooseDeepTau2017v2p1VSjet_reco", &tauVVLooseDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSjet_reco", &tauVLooseDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSjet_reco", &tauLooseDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSjet_reco", &tauMediumDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byTightDeepTau2017v2p1VSjet_reco", &tauTightDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byVTightDeepTau2017v2p1VSjet_reco", &tauVTightDeepTau2017v2p1VSjetRecoVector_);
    recoTree_->SetBranchAddress("tau_byVVTightDeepTau2017v2p1VSjet_reco", &tauVVTightDeepTau2017v2p1VSjetRecoVector_);
    //DeepTau vs Electrons
    recoTree_->SetBranchAddress("tau_VVVLooseDeepTau2017v2p1VSe_reco", &tauVVVLooseDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_VVLooseDeepTau2017v2p1VSe_reco", &tauVVLooseDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_VLooseDeepTau2017v2p1VSe_reco", &tauVLooseDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_LooseDeepTau2017v2p1VSe_reco", &tauLooseDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_MediumDeepTau2017v2p1VSe_reco", &tauMediumDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_TightDeepTau2017v2p1VSe_reco", &tauTightDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_VTightDeepTau2017v2p1VSe_reco", &tauVTightDeepTau2017v2p1VSeRecoVector_);
    recoTree_->SetBranchAddress("tau_VVTightDeepTau2017v2p1VSe_reco", &tauVVTightDeepTau2017v2p1VSeRecoVector_);
    //DeepTau vs Muons
    recoTree_->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSmu_reco", &tauVLooseDeepTau2017v2p1VSmuRecoVector_);
    recoTree_->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSmu_reco", &tauLooseDeepTau2017v2p1VSmuRecoVector_);
    recoTree_->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSmu_reco", &tauMediumDeepTau2017v2p1VSmuRecoVector_);
    recoTree_->SetBranchAddress("tau_byTightDeepTau2017v2p1VSmu_reco", &tauTightDeepTau2017v2p1VSmuRecoVector_);
    //
    recoTree_->SetBranchAddress("tau_decayMode_reco", &tauDecayModeRecoVector_);
    recoTree_->SetBranchAddress("METFixEE2017_E_reco", &METEReco_);
    recoTree_->SetBranchAddress("METFixEE2017_phi_reco", &METPhiReco_);
    //GEN container
    genTree_->SetBranchAddress("tau_vis_n_gen", &tauVisNGen_);
    genTree_->SetBranchAddress("tau_E_gen", &tauEGenVector_);
    genTree_->SetBranchAddress("tau_px_gen", &tauPxGenVector_);
    genTree_->SetBranchAddress("tau_py_gen", &tauPyGenVector_);
    genTree_->SetBranchAddress("tau_pz_gen", &tauPzGenVector_);
    genTree_->SetBranchAddress("tau_vis_E_gen", &tauVisEGenVector_);
    genTree_->SetBranchAddress("tau_vis_px_gen", &tauVisPxGenVector_);
    genTree_->SetBranchAddress("tau_vis_py_gen", &tauVisPyGenVector_);
    genTree_->SetBranchAddress("tau_vis_pz_gen", &tauVisPzGenVector_);
    genTree_->SetBranchAddress("METFixEE2017_E_gen", &METEGen_);
    genTree_->SetBranchAddress("METFixEE2017_phi_gen", &METPhiGen_);

    isInputInitialised_ = true;
  }

  void Input::FinaliseInput(void)
  {
    inFile_->Close();
    isInputInitialised_ = false;
  }

  void Input::LoadNewEvent(int iEvent)
  {
    recoTree_->GetEntry(iEvent);
    genTree_->GetEntry(iEvent);
  }

  /*************/
  /* RECO Taus */
  /*************/
  int Input::GetTauNReco(){ return tauNReco_; }

  double Input::GetTauEReco(int iTau){ return tauERecoVector_->at(iTau); }

  double Input::GetTauPxReco(int iTau){ return tauPxRecoVector_->at(iTau); }

  double Input::GetTauPyReco(int iTau){ return tauPyRecoVector_->at(iTau); }

  double Input::GetTauPzReco(int iTau){ return tauPzRecoVector_->at(iTau); }

  double Input::GetTaudXYReco(int iTau){ return taudXYRecoVector_->at(iTau); }

  double Input::GetTaudZReco(int iTau){ return taudZRecoVector_->at(iTau); }

  bool Input::IsTauDeepIDvsElReco(int iTau, const std::string& deepTauIDwp)
  {
    switch(tauIDwpMap_[deepTauIDwp])
    {
      case 0 : return tauVVVLooseDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break;
      case 1 : return tauVVLooseDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break; 
      case 2 : return tauVLooseDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break; 
      case 3 : return tauLooseDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break; 
      case 4 : return tauMediumDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break;
      case 5 : return tauTightDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break;
      case 6 : return tauVTightDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break;
      case 7 : return tauVVTightDeepTau2017v2p1VSeRecoVector_->at(iTau) == 1; break;
      default : throw std::runtime_error("Deep Tau ID vs Electron not defined");
    }
  }

  bool Input::IsTauDeepIDvsJetReco(int iTau, const std::string& deepTauIDwp)
  {
    switch(tauIDwpMap_[deepTauIDwp])
    {
      case 0 : return tauVVVLooseDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break;
      case 1 : return tauVVLooseDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break; 
      case 2 : return tauVLooseDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break; 
      case 3 : return tauLooseDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break; 
      case 4 : return tauMediumDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break;
      case 5 : return tauTightDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break;
      case 6 : return tauVTightDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break;
      case 7 : return tauVVTightDeepTau2017v2p1VSjetRecoVector_->at(iTau) == 1; break;
      default : throw std::runtime_error("Deep Tau ID vs Jet not defined");
    }
  }

  bool Input::IsTauDeepIDvsMuReco(int iTau, const std::string& deepTauIDwp)
  {
    switch(tauIDwpMap_[deepTauIDwp])
    {
      case 2 : return tauVLooseDeepTau2017v2p1VSmuRecoVector_->at(iTau) == 1; break; 
      case 3  : return tauLooseDeepTau2017v2p1VSmuRecoVector_->at(iTau) == 1; break; 
      case 4 : return tauMediumDeepTau2017v2p1VSmuRecoVector_->at(iTau) == 1; break;
      case 5  : return tauTightDeepTau2017v2p1VSmuRecoVector_->at(iTau) == 1; break;
      default : throw std::runtime_error("Deep Tau ID vs Muon not defined");
    }
  }

  double Input::GetMETEReco(){ return METEReco_; }
  double Input::GetMETPhiReco(){ return METPhiReco_; }

  /************/
  /* GEN Taus */
  /************/
  int Input::GetTauVisNGen(){ return tauVisNGen_; }

  double Input::GetTauVisEGen(int iTau){ return tauVisEGenVector_->at(iTau); }

  double Input::GetTauVisPxGen(int iTau){ return tauVisPxGenVector_->at(iTau); }

  double Input::GetTauVisPyGen(int iTau){ return tauVisPyGenVector_->at(iTau); }
  
  double Input::GetTauVisPzGen(int iTau){ return tauVisPzGenVector_->at(iTau); }

  double Input::GetTauEGen(int iTau){ return tauEGenVector_->at(iTau); }

  double Input::GetTauPxGen(int iTau){ return tauPxGenVector_->at(iTau); }

  double Input::GetTauPyGen(int iTau){ return tauPyGenVector_->at(iTau); }
  
  double Input::GetTauPzGen(int iTau){ return tauPzGenVector_->at(iTau); }

  double Input::GetMETEGen(){ return METEGen_; }

  double Input::GetMETPhiGen(){ return METPhiGen_; }

}//namespace files
