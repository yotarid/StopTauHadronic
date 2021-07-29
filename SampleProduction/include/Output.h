#ifndef OUTPUT_H
#define OUTPUT_H

#include "../utils/easylogging++.h"
#include "../utils/consolecolor.h"

#include <map>
#include <iostream>
#include <string>
#include <cstdlib>

#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TBranch.h"

namespace out {
  class Output {
    public : 
      explicit Output(const std::string& era, const std::string& process, const std::string& channel, const std::string& outFileName);
      ~Output();

      TFile* GetFile(void);
      std::string GetFilePath(void);

      TTree* GetRecoSelTree(void);
      int GetRecoSelTreeNEvents(void);

      TTree* GetGenSelTree(void);
      int GetGenSelTreeNEvents(void);

      void InitialiseOutput(void);
      void LoadNewEvent(void);
      void FinaliseOutput(void);

      void SetRecoTauE(int tauIdx, double tauE);
      void SetRecoTauPx(int tauIdx, double tauPx);
      void SetRecoTauPy(int tauIdx, double tauPy);
      void SetRecoTauPz(int tauIdx, double tauPz);
      void SetRecoTauPt(int tauIdx, double tauPt);
      void SetRecoTaudXY(int tauIdx, double taudXY);
      void SetRecoTaudZ(int tauIdx, double taudZ);
      void SetRecoTauDeepTauIDvsJet(int tauIdx, const std::string& deepTauIDwp);
      void SetRecoTauDeepTauIDvsEl(int tauIdx, const std::string& deepTauIDwp);
      void SetRecoTauDeepTauIDvsMu(int tauIdx, const std::string& deepTauIDwp);
      void SetRecoTauDecayMode(int tauIdx, double tauDecayMode);
      void SetRecoTauPairHT(double tauPairHT);
      void SetRecoTauPairmT2(double tauPairmT2);
      void SetRecoTauPairMETE(double tauPairMETE);
      void SetRecoTauPairMETPhi(double tauPairMETPhi);


    private :
      std::string era_, process_, channel_;

      TFile* outFile_;
      TDirectory* outROOTDir_;
      std::string outFilePath_;

      TTree *recoSelTree_, *genSelTree_;
      int recoSelNEvents_, genSeleNEvents_;

      bool isOutputInitialised_ = false;

      double recoTau1E_ = 0, 
             recoTau1Px_ = 0, recoTau1Py_ = 0, recoTau1Pz_ = 0, recoTau1Pt_ = 0,
             recoTau1dXY_ = 0, recoTau1dZ_ = 0,
             recoTau1DeepTauIDvsJet_ = -1,
             recoTau1DeepTauIDvsEl_ = -1,
             recoTau1DeepTauIDvsMu_ = -1,
             recoTau1DecayMode_ = 0;

      double recoTau2E_ = 0, 
             recoTau2Px_ = 0, recoTau2Py_ = 0, recoTau2Pz_ = 0, recoTau2Pt_ = 0,
             recoTau2dXY_ = 0, recoTau2dZ_ = 0,
             recoTau2DeepTauIDvsJet_ = -1,
             recoTau2DeepTauIDvsEl_ = -1,
             recoTau2DeepTauIDvsMu_ = -1,
             recoTau2DecayMode_ = 0;

      double recoTauPairHT_ = 0;
      double recoTauPairmT2_ = 0;
      double recoTauPairMETE_ = 0;
      double recoTauPairMETPhi_ = 0;

      //Tau ID working point map
      std::map<std::string, int> tauIDwpMap_ = {{"VVVLoose", 0}, {"VVLoose", 1}, {"VLoose", 2}, {"Loose", 3}, {"Medium", 4}, {"Tight", 5}, {"VTight", 6}, {"VVTight", 7}};

  };

}//namespace out

#endif
