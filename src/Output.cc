#include "../include/Output.h"

namespace out {

  Output::Output(const std::string& era, const std::string& process, const std::string& channel, const std::string& outFileName)
    : era_(era), process_(process), channel_(channel)
  {
    std::string outDirPath = Form("%s/%s/%s/%s", std::getenv("SAMPLEPRODUCTION_OUT_DIR"), era.c_str(), process.c_str(), channel.c_str());
    LOG(INFO) << "" << RESET;
    LOG(INFO) << BOLDGREEN << "Era : " << WHITE << era << BOLDGREEN << ", Process : " << WHITE << process << BOLDGREEN << ", Channel : " << WHITE << channel << RESET;
    LOG(INFO) << BOLDYELLOW << "\tCreating output directory : " << WHITE << outDirPath << RESET;
    system(Form("mkdir -p %s", outDirPath.c_str()));
    //
    LOG(INFO) << BOLDYELLOW << "\t\tCreating output file : " << WHITE << Form("%s/%s.root", outDirPath.c_str(), outFileName.c_str()) << RESET;
    outFile_ = TFile::Open(Form("%s/%s.root", outDirPath.c_str(), outFileName.c_str()), "RECREATE");
    outFilePath_ = outDirPath + "/" + outFileName;
    if(!outFile_)
      throw std::runtime_error("Output:Output : ROOT File is nullptr");
    //
    LOG(INFO) << BOLDYELLOW << "\t\t\tCreating ROOT directory : " << WHITE << "miniaodsim2custom2custom" << RESET;
    outROOTDir_ = outFile_->mkdir("miniaodsim2custom2custom");
    if(!outROOTDir_)
      throw std::runtime_error("Output:Output : ROOT Directory is nullptr");
    outROOTDir_->cd();
    //
    recoSelTree_ = new TTree("reco", "Selection of reconstructed events");
    genSelTree_ = new TTree("gen", "Selection of generated events");
    if(!recoSelTree_ || !genSelTree_)
      throw std::runtime_error("Output:Output : RECO/GEN Tree is nullptr");
  }

  Output::~Output()
  {
    //LOG(INFO) << BOLDYELLOW << "\t\tClosing output file : " << WHITE << outFilePath_ << RESET;
    outFile_->Close();
  }

  TFile* Output::GetFile(void){ return outFile_; }

  std::string Output::GetFilePath(void){ return outFilePath_; }

  TTree* Output::GetRecoSelTree(void){ return recoSelTree_; }

  int Output::GetRecoSelTreeNEvents(void){ return (int)recoSelTree_->GetEntries(); }

  TTree* Output::GetGenSelTree(void){ return genSelTree_; }

  int Output::GetGenSelTreeNEvents(void){ return (int)genSelTree_->GetEntries(); }

  void Output::InitialiseOutput(void)
  {
    //Tau1
    recoSelTree_->Branch("tau1_E_reco", &recoTau1E_);
    recoSelTree_->Branch("tau1_px_reco", &recoTau1Px_);
    recoSelTree_->Branch("tau1_py_reco", &recoTau1Py_);
    recoSelTree_->Branch("tau1_pz_reco", &recoTau1Pz_);
    recoSelTree_->Branch("tau1_pt_reco", &recoTau1Pt_);
    recoSelTree_->Branch("tau1_dxy_reco", &recoTau1dXY_);
    recoSelTree_->Branch("tau1_dz_reco", &recoTau1dZ_);
    recoSelTree_->Branch("tau1_DeepTauIDvsJet_reco", &recoTau1DeepTauIDvsJet_);
    recoSelTree_->Branch("tau1_DeepTauIDvsEl_reco", &recoTau1DeepTauIDvsEl_);
    recoSelTree_->Branch("tau1_DeepTauIDvsMu_reco", &recoTau1DeepTauIDvsMu_);
    recoSelTree_->Branch("tau1_decayMode_reco", &recoTau1DecayMode_);
    //Tau2tau
    recoSelTree_->Branch("tau2_px_reco", &recoTau2Px_);
    recoSelTree_->Branch("tau2_py_reco", &recoTau2Py_);
    recoSelTree_->Branch("tau2_pz_reco", &recoTau2Pz_);
    recoSelTree_->Branch("tau2_pt_reco", &recoTau2Pt_);
    recoSelTree_->Branch("tau2_dxy_reco", &recoTau2dXY_);
    recoSelTree_->Branch("tau2_dz_reco", &recoTau2dZ_);
    recoSelTree_->Branch("tau2_DeepTauIDvsJet_reco", &recoTau2DeepTauIDvsJet_);
    recoSelTree_->Branch("tau2_DeepTauIDvsEl_reco", &recoTau2DeepTauIDvsEl_);
    recoSelTree_->Branch("tau2_DeepTauIDvsMu_reco", &recoTau2DeepTauIDvsMu_);
    recoSelTree_->Branch("tau2_decayMode_reco", &recoTau2DecayMode_);
    //Tau pairtau
    recoSelTree_->Branch("tau_pair_MET_E_reco", &recoTauPairMETE_);
    recoSelTree_->Branch("tau_pair_MET_phi_reco", &recoTauPairMETPhi_);
    recoSelTree_->Branch("tau_pair_HT_reco", &recoTauPairHT_);
    recoSelTree_->Branch("tau_pair_mT2_reco", &recoTauPairmT2_);

    isOutputInitialised_ = true;
  }

  void Output::LoadNewEvent(void)
  {  
    recoSelTree_->Fill();
    genSelTree_->Fill();
  }  

  void Output::FinaliseOutput(void)
  {
    //LOG(INFO) << BOLDMAGENTA << "\t Closing output file : " << WHITE << outFilePath_ << RESET;
    LOG(INFO) << " " << RESET;
    outFile_->Write();
    outFile_->Close();
    isOutputInitialised_ = false;
  }

  void Output::SetRecoTauE(int tauIdx, double tauE)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1E_ = tauE; break;
      case 2 : recoTau2E_ = tauE; break;
      default : throw std::runtime_error("Output::SetRecoTauE : undefined Tau index");
    }
  }

  void Output::SetRecoTauPx(int tauIdx, double tauPx)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1Px_ = tauPx; break;
      case 2 : recoTau2Px_ = tauPx; break;
      default : throw std::runtime_error("Output::SetRecoTauPx : undefined Tau index");
    }
  }

  void Output::SetRecoTauPy(int tauIdx, double tauPy)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1Py_ = tauPy; break;
      case 2 : recoTau2Py_ = tauPy; break;
      default : throw std::runtime_error("Output::SetRecoTauPy : undefined Tau index");
    }
  }

  void Output::SetRecoTauPz(int tauIdx, double tauPz)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1Pz_ = tauPz; break;
      case 2 : recoTau2Pz_ = tauPz; break;
      default : throw std::runtime_error("Output::SetRecoTauPz : undefined Tau index");
    }
  }

  void Output::SetRecoTauPt(int tauIdx, double tauPt)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1Pt_ = tauPt; break;
      case 2 : recoTau2Pt_ = tauPt; break;
      default : throw std::runtime_error("Output::SetRecoTauPt : undefined Tau index");
    }
  }

  void Output::SetRecoTaudXY(int tauIdx, double taudXY)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1dXY_ = taudXY; break;
      case 2 : recoTau2dXY_ = taudXY; break;
      default : throw std::runtime_error("Output::SetRecoTaudXY : undefined Tau index");
    }
  }

  void Output::SetRecoTaudZ(int tauIdx, double taudZ)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1dZ_ = taudZ; break;
      case 2 : recoTau2dZ_ = taudZ; break;
      default : throw std::runtime_error("Output::SetRecoTaudZ : undefined Tau index");
    }
  }

  void Output::SetRecoTauDeepTauIDvsJet(int tauIdx, const std::string& deepTauIDwp)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1DeepTauIDvsJet_ = tauIDwpMap_[deepTauIDwp]; break;
      case 2 : recoTau2DeepTauIDvsJet_ = tauIDwpMap_[deepTauIDwp]; break;
      default : throw std::runtime_error("Output::SetRecoTauDeepTauIDvsJet : undefined Tau index");
    }
  }

  void Output::SetRecoTauDeepTauIDvsEl(int tauIdx, const std::string& deepTauIDwp)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1DeepTauIDvsEl_ = tauIDwpMap_[deepTauIDwp]; break;
      case 2 : recoTau2DeepTauIDvsEl_ = tauIDwpMap_[deepTauIDwp]; break;
      default : throw std::runtime_error("Output::SetRecoTauDeepTauIDvsEl : undefined Tau index");
    }
  }

  void Output::SetRecoTauDeepTauIDvsMu(int tauIdx, const std::string& deepTauIDwp)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1DeepTauIDvsMu_ = tauIDwpMap_[deepTauIDwp]; break;
      case 2 : recoTau2DeepTauIDvsMu_ = tauIDwpMap_[deepTauIDwp]; break;
      default : throw std::runtime_error("Output::SetRecoTauDeepTauIDvsMu : undefined Tau index");
    }
  }

  void Output::SetRecoTauDecayMode(int tauIdx, double tauDecayMode)
  {
    switch(tauIdx)
    {
      case 1 : recoTau1DecayMode_ = tauDecayMode; break;
      case 2 : recoTau2DecayMode_ = tauDecayMode; break;
      default : throw std::runtime_error("Output::SetRecoTauDecayMode : undefined Tau index");
    }
  }

  void Output::SetRecoTauPairHT(double tauPairHT){ recoTauPairHT_ = tauPairHT; }

  void Output::SetRecoTauPairmT2(double tauPairmT2){ recoTauPairmT2_ = tauPairmT2; }

  void Output::SetRecoTauPairMETE(double tauPairMETE){ recoTauPairMETE_ = tauPairMETE; }

  void Output::SetRecoTauPairMETPhi(double tauPairMETPhi){ recoTauPairMETPhi_ = tauPairMETPhi; }

}//namespace out
