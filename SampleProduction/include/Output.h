#ifndef OUTPUT_H
#define OUTPUT_H

namespace out {
  class Output {
    public : 
      explicit Output(const std::string& outFilePath);
      ~Output() {}

      TFile* GetOutFile();
      std::string GetOutFilePath();

      TTree* GetRecoSelTree();
      int GetRecoSelTreeNEvents();

      TTree* GetGenSelTree();
      int GetGenSelTreeNEvents();

      void InitialiseEvent();
      void LoadNewEvent();

      void Set

    private :
      TFile* outFile_;
      std::string outFilePath_;

      TTree *recoSelTree_, *genSelTree_;
      int recoSelNEvents_, genSeleNEvents_;

      bool isEventInitialised = false;

      double tau1EReco_ = 0, 
             tau1PxReco_ = 0, tau1PyReco_ = 0, tau1PzReco_ = 0,
             tau1dXYReco_ = 0, tau1dZReco_ = 0,
             tau1DeepTauIDvsJetReco_ = -1;
             tau1DeepTauIDvsElReco_ = -1;
             tau1DeepTauIDvsMuReco_ = -1;
             tau1DecayModeReco_ = 0;

      double tau2EReco_ = 0, 
             tau2PxReco_ = 0, tau2PyReco_ = 0, tau2PzReco_ = 0,
             tau2dXYReco_ = 0, tau2dZReco_ = 0,
             tau2DeepTauIDvsJetReco_ = -1;
             tau2DeepTauIDvsElReco_ = -1;
             tau2DeepTauIDvsMuReco_ = -1;
             tau2DecayModeReco_ = 0;

      double tauPairHTReco_ = 0;
      double tauPairmT2Reco_ = 0;
      double tauPairMETEReco_ = 0;
      double tauPairMETPhiReco_ = 0;

      //Tau ID working point map
      std::map<std::string, int> tauIDwpMap_ = {{"VVVLoose", 0}, {"VVLoose", 1}, {"VLoose", 2}, {"Loose", 3}, {"Medium", 4}, {"Tight", 5}, {"VTight", 6}, {"VVTight", 7}};

  };

}//namespace out

#endif