#include "../include/Output.h"

namespace out {

  Output::Output(const std::string& outDirPath, const std::string& outFileName)
  {
    std::cout << "Creating output directory : " << outFilePath << std::endl;
    system(Form("mkdir -p %s", outFilePath.c_str()));
    std::cout << "Creating output file : " << Form("%s/%s", outFilePath.c_str(), outFileName.c_str()) << std::endl;
    outFile_ = TFile::Open(Form("%s/%s", outDirPath.c_str(), outFileName.c_str()));
    outFilePath_ = outDirPath + outFileName;
    std::cout << "Creating ROOT directory inside output file : miniaodsim2custom2custom" << std::endl;
    TDirectory *outROOTDir = outFile_->mkdir("miniaodsim2custom2custom");
    outROOTDir->cd();
    recoSelTree_ = new TTree("reco", "Selection of reconstructed events");
    genSelTree_ = new TTree("gen", "Selection of generated events");
    if(!outFile_ || recoSelTree_ || genSelTree_)
      throw std::runtime_error("Output:Output : File, RECO or GEN tree is nullptr");
  }

  TFile* Output::GetOutFile(){ return outFile_; }

  std::string Output::GetOutFilePath{ return outFilePath_; }

  TTree* Output::GetRecoSelTree(){ return recoSelTree_; }

  int Output::GetRecoSelTreeNEvents(){ return (int)recoSelTree_->GetEntries(); }

  TTree* Output::GetGenSelTree(){ return genSelTree_; }

  int Output::GetGenSelTreeNEvents(){ return (int)genSelTree_->GetEntries(); }

  void Output::InitialiseEvent()
  {
    //Tau1
    recoSelTree_->Branch("tau1_E_reco", &tau1EReco_);
    recoSelTree_->Branch("tau1_px_reco", &tau1PxReco_);
    recoSelTree_->Branch("tau1_py_reco", &tau1PyReco_);
    recoSelTree_->Branch("tau1_pz_reco", &tau1PzReco_);
    recoSelTree_->Branch("tau1_dxy_reco", &tau1dXYReco_);
    recoSelTree_->Branch("tau1_dz_reco", &tau1dZReco_);
    recoSelTree_->Branch("tau1_DeepTauIDvsJet_reco", tau1DeepTauIDvsJetReco_);
    recoSelTree_->Branch("tau1_DeepTauIDvsEl_reco", tau1DeepTauIDvsElReco_);
    recoSelTree_->Branch("tau1_DeepTauIDvsMu_reco", tau1DeepTauIDvsMuReco_);
    recoSelTree_->Branch("tau1_decayMode_reco", tau1DecayModeReco_);

    //Tau2
    recoSelTree_->Branch("tau2_E_reco", &tau2EReco_);
    recoSelTree_->Branch("tau2_px_reco", &tau2PxReco_);
    recoSelTree_->Branch("tau2_py_reco", &tau2PyReco_);
    recoSelTree_->Branch("tau2_pz_reco", &tau2PzReco_);
    recoSelTree_->Branch("tau2_dxy_reco", &tau2dXYReco_);
    recoSelTree_->Branch("tau2_dz_reco", &tau2dZReco_);
    recoSelTree_->Branch("tau2_DeepTauIDvsJet_reco", tau2DeepTauIDvsJetReco_);
    recoSelTree_->Branch("tau2_DeepTauIDvsEl_reco", tau2DeepTauIDvsElReco_);
    recoSelTree_->Branch("tau2_DeepTauIDvsMu_reco", tau2DeepTauIDvsMuReco_);
    recoSelTree_->Branch("tau2_decayMode_reco", tau2DecayModeReco_);

    //Tau pair
    recoSelTree_->Branch("tau_pair_MET_E_reco", tauPairMETEReco_);
    recoSelTree_->Branch("tau_pair_MET_phi_reco", tauPairMETPhiReco_);
    recoSelTree_->Branch("tau_pair_HT_reco", tauPairHTReco_);
    recoSelTree_->Branch("tau_pair_mT2_reco", tauPairmT2Reco_);

    isEventInitialised_ = true;
  }

  void Output::LoadNewEvent()
  {  
    recoSelTree_->Fill();
    genSelTree_->Fill();
  }  


  void Output::SetTauEReco(int tauIdx, double tauE)
  {
    switch(tauIdx)
    {
      case 1 : tau1EReco_ = tauE; break;
      case 2 : tau2EReco_ = tauE; break;
      default : throw std::runtime_error("Output::SetTauEReco : undefined Tau index");
    }
  }

  void Output::SetTauPxReco(int tauIdx, double tauPx)
  {
    switch(tauIdx)
    {
      case 1 : tau1PxReco_ = tauPx; break;
      case 2 : tau2PxReco_ = tauPx; break;
      default : throw std::runtime_error("Output::SetTauPxReco : undefined Tau index");
    }
  }

  void Output::SetTauPyReco(int tauIdx, double tauPy)
  {
    switch(tauIdx)
    {
      case 1 : tau1PyReco_ = tauPy; break;
      case 2 : tau2PyReco_ = tauPy; break;
      default : throw std::runtime_error("Output::SetTauPyReco : undefined Tau index");
    }
  }

  void Output::SetTauPzReco(int tauIdx, double tauPz)
  {
    switch(tauIdx)
    {
      case 1 : tau1PzReco_ = tauPz; break;
      case 2 : tau2PzReco_ = tauPz; break;
      default : throw std::runtime_error("Output::SetTauPzReco : undefined Tau index");
    }
  }

  void Output::SetTaudXYReco(int tauIdx, double taudXY)
  {
    switch(tauIdx)
    {
      case 1 : tau1dXYReco_ = taudXY; break;
      case 2 : tau2dXYReco_ = taudXY; break;
      default : throw std::runtime_error("Output::SetTaudXYReco : undefined Tau index");
    }
  }

  void Output::SetTaudZReco(int tauIdx, double taudZ)
  {
    switch(tauIdx)
    {
      case 1 : tau1dZReco_ = taudZ; break;
      case 2 : tau2dZReco_ = taudZ; break;
      default : throw std::runtime_error("Output::SetTaudZReco : undefined Tau index");
    }
  }

  void Output::SetTauDeepTauIDvsJetReco(int tauIdx, const std::string& deepTauIDwp)
  {
    switch(tauIdx)
    {
      case 1 : tau1DeepTauIDvsJetReco_ = tauIDwpMap[deepTauIDwp]; break;
      case 2 : tau2DeepTauIDvsJetReco_ = tauIDwpMap[deepTauIDwp]; break;
      default : throw std::runtime_error("Output::SetTauDeepTauIDvsJetReco : undefined Tau index");
    }
  }

  void Output::SetTauDeepTauIDvsElReco(int tauIdx, const std::string& deepTauIDwp)
  {
    switch(tauIdx)
    {
      case 1 : tau1DeepTauIDvsElReco_ = tauIDwpMap[deepTauIDwp]; break;
      case 2 : tau2DeepTauIDvsElReco_ = tauIDwpMap[deepTauIDwp]; break;
      default : throw std::runtime_error("Output::SetTauDeepTauIDvsElReco : undefined Tau index");
    }
  }

  void Output::SetTauDeepTauIDvsMuReco(int tauIdx, const std::string& deepTauIDwp)
  {
    switch(tauIdx)
    {
      case 1 : tau1DeepTauIDvsMuReco_ = tauIDwpMap[deepTauIDwp]; break;
      case 2 : tau2DeepTauIDvsMuReco_ = tauIDwpMap[deepTauIDwp]; break;
      default : throw std::runtime_error("Output::SetTauDeepTauIDvsMuReco : undefined Tau index");
    }
  }

  void Output::SetTauDecayModeReco(int tauIdx, double tauDecayMode)
  {
    switch(tauIdx)
    {
      case 1 : tau1DecayModeReco_ = tauDecayMode; break;
      case 2 : tau2DecayModeReco_ = tauDecayMode; break;
      default : throw std::runtime_error("Output::SetTauDecayModeReco : undefined Tau index");
    }
  }

  void Output::SetTauPairHTReco(double tauPairHT){ tauPairHTReco_ = tauPairHT; }

  void Output::SetTauPairmT2Reco(double tauPairmT2){ tauPairmT2Reco_ = tauPairmT2; }

  void Output::SetTauPairMETEReco(double tauPairMETE){ tauPairMETEReco_ = tauPairMETE; }

  void Output::SetTauPairMETPhiReco(double tauPairMETPhi){ tauPairMETPhiReco_ = tauPairMETPhi; }

}//namespace out