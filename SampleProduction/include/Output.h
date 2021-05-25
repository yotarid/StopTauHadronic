#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <map>
#include <iostream>

#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TBranch.h"

namespace out {
  class Output {
    public : 
      explicit Output(const std::string& outDirPath, const std::string& outFileName);
      ~Output() {}

      TFile* GetOutFile();
      std::string GetOutFilePath();

      TTree* GetRecoSelTree();
      int GetRecoSelTreeNEvents();

      TTree* GetGenSelTree();
      int GetGenSelTreeNEvents();

      void InitialiseEvent();
      void LoadNewEvent();

      void SetTauEReco(int tauIdx, double tauE);
      void SetTauPxReco(int tauIdx, double tauPx);
      void SetTauPyReco(int tauIdx, double tauPy);
      void SetTauPzReco(int tauIdx, double tauPz);
      void SetTaudXYReco(int tauIdx, double taudXY);
      void SetTaudZReco(int tauIdx, double taudZ);
      void SetTauDeepTauIDvsJetReco(int tauIdx, const std::string& deepTauIDwp);
      void SetTauDeepTauIDvsElReco(int tauIdx, const std::string& deepTauIDwp);
      void SetTauDeepTauIDvsMuReco(int tauIdx, const std::string& deepTauIDwp);
      void SetTauDecayModeReco(int tauIdx, double tauDecayMode);
      void SetTauPairHTReco(double tauPairHT);
      void SetTauPairmT2Reco(double tauPairmT2);
      void SetTauPairMETEReco(double tauPairMETE);
      void SetTauPairMETPhiReco(double tauPairMETPhi);


    private :
      TFile* outFile_;
      TDirectory* outROOTDir_;
      std::string outFilePath_;

      TTree *recoSelTree_, *genSelTree_;
      int recoSelNEvents_, genSeleNEvents_;

      bool isEventInitialised_ = false;

      double tau1EReco_ = 0, 
             tau1PxReco_ = 0, tau1PyReco_ = 0, tau1PzReco_ = 0,
             tau1dXYReco_ = 0, tau1dZReco_ = 0,
             tau1DeepTauIDvsJetReco_ = -1,
             tau1DeepTauIDvsElReco_ = -1,
             tau1DeepTauIDvsMuReco_ = -1,
             tau1DecayModeReco_ = 0;

      double tau2EReco_ = 0, 
             tau2PxReco_ = 0, tau2PyReco_ = 0, tau2PzReco_ = 0,
             tau2dXYReco_ = 0, tau2dZReco_ = 0,
             tau2DeepTauIDvsJetReco_ = -1,
             tau2DeepTauIDvsElReco_ = -1,
             tau2DeepTauIDvsMuReco_ = -1,
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