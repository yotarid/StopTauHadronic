#include "../utils/argvparser/argvparser.h"
#include "../utils/easylogging/easylogging++.h"
#include "../utils/easylogging/consolecolor.h"

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TApplication.h"
#include <TSystem.h>
#include <TStyle.h>

INITIALIZE_EASYLOGGINGPP

using namespace CommandLineProcessing;

int main (int argc, char* argv[])
{
  el::Configurations logConfig(std::string(std::getenv("SAMPLEPRODUCTION_BASE_DIR")) + "/settings/logger.conf");
  el::Loggers::reconfigureAllLoggers(logConfig);

  ArgvParser cmd;  

  cmd.addErrorCode(0, "Success");
  cmd.addErrorCode(1, "Error");
  // options
  cmd.setHelpOption("h", "help", "Print this help page");
  //
  cmd.defineOption("file1", "Output file 1", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("file1", "f1");
  //
  cmd.defineOption("file2", "Output file 2", ArgvParser::OptionRequiresValue);
  cmd.defineOptionAlternative("file2", "f2");

  int result = cmd.parse(argc, argv);
  if(result != ArgvParser::NoParserError)
  {
      LOG(INFO) << cmd.parseErrorDescription(result) << RESET;
      exit(1);
  }

  std::string filePath1 = cmd.foundOption("file1") ? cmd.optionValue("file1") : "";
  std::string filePath2 = cmd.foundOption("file2") ? cmd.optionValue("file2") : "";

  TApplication* theApp = new TApplication("App", 0, 0);

  // double tau1E , tau1Px , tau1Py , tau1Pz , tau1Pt , tau1dXY , tau1dZ;
  // double tau2E , tau2Px , tau2Py , tau2Pz , tau2Pt , tau2dXY , tau2dZ;
  double tauPair1MET, tauPair1HT, tauPair1mT2;
  double tauPair2MET, tauPair2HT, tauPair2mT2;

  TFile* file1 = TFile::Open(filePath1.c_str());
  TTree* recoTree1 = (TTree*)file1->Get("miniaodsim2custom2custom/reco");
  recoTree1->SetBranchAddress("tau_pair_MET_E_reco", &tauPair1MET);
  recoTree1->SetBranchAddress("tau_pair_HT_reco", &tauPair1HT);
  recoTree1->SetBranchAddress("tau_pair_mT2_reco", &tauPair1mT2);
  
  TFile* file2 =  TFile::Open(filePath2.c_str());
  TTree* recoTree2 = (TTree*)file2->Get("miniaodsim2custom2custom/reco");
  recoTree2->SetBranchAddress("tau_pair_MET_E_reco", &tauPair2MET);
  recoTree2->SetBranchAddress("tau_pair_HT_reco", &tauPair2HT);
  recoTree2->SetBranchAddress("tau_pair_mT2_reco", &tauPair2mT2);

  TCanvas* c1TauPairMET = new TCanvas("c1TauPairMET", "c1TauPairMET");
  TH1D* h1TauPair1MET = new TH1D("h1TauPair1MET", "TauPairMET_25GeV", 100, 0, 1000);
  TH1D* h1TauPair2MET = new TH1D("h1TauPair2MET", "TauPair2MET_40GeV", 100, 0, 1000);

  TCanvas* c1TauPairHT = new TCanvas("c1TauPairHT", "c1TauPairHT");
  TH1D* h1TauPair1HT = new TH1D("h1TauPair1HT", "TauPair1HT_25GeV", 100, 0, 1000);
  TH1D* h1TauPair2HT = new TH1D("h1TauPair2HT", "TauPair2HT_40GeV", 100, 0, 1000);

  TCanvas* c1TauPairmT2 = new TCanvas("c1TauPairmT2", "c1TauPairmT2");
  TH1D* h1TauPair1mT2 = new TH1D("h1TauPair1mT2", "TauPair1mT2_25GeV", 100, 0, 500);
  TH1D* h1TauPair2mT2 = new TH1D("h1TauPair2mT2", "TauPair2mT2_40GeV", 100, 0, 500);

  int nEntries1 = (int)recoTree1->GetEntries();
  for (int iEntry = 0; iEntry < nEntries1; iEntry++)
  {
    recoTree1->GetEntry(iEntry);
    h1TauPair1MET->Fill(tauPair1MET);
    h1TauPair1HT->Fill(tauPair1HT);
    h1TauPair1mT2->Fill(tauPair1MET);
  }

  int nEntries2 = (int)recoTree2->GetEntries();
  for (int iEntry = 0; iEntry < nEntries2; iEntry++)
  {
    recoTree2->GetEntry(iEntry);
    h1TauPair2MET->Fill(tauPair2MET);
    h1TauPair2HT->Fill(tauPair2HT);
    h1TauPair2mT2->Fill(tauPair2MET);
  }

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  /***************/
  /***** MET *****/
  /***************/
  c1TauPairMET->cd();
  //
  h1TauPair1MET->SetLineColor(4);
  h1TauPair1MET->SetLineWidth(2);
  h1TauPair1MET->GetXaxis()->SetTitle("MET");
  h1TauPair1MET->Draw();
  //
  h1TauPair2MET->SetLineColor(6);
  h1TauPair2MET->SetLineWidth(2);
  h1TauPair2MET->Draw("SAME");
  //
  TLegend* lMET = new TLegend(0.8, 0.9, 0.8, 0.9);
  lMET->SetTextSize(0.04);
  lMET->AddEntry(h1TauPair1MET, "p_{T} > 25GeV");
  lMET->AddEntry(h1TauPair2MET, "p_{T} > 40GeV");
  lMET->Draw();
  c1TauPairMET->Update();

  /**************/
  /***** HT *****/
  /**************/
  c1TauPairHT->cd();
  //
  h1TauPair1HT->SetLineColor(4);
  h1TauPair1HT->SetLineWidth(2);
  h1TauPair1HT->GetXaxis()->SetTitle("HT");
  h1TauPair1HT->Draw();
  //
  h1TauPair2HT->SetLineColor(6);
  h1TauPair2HT->SetLineWidth(2);
  h1TauPair2HT->Draw("SAME");
  //
  TLegend* lHT = new TLegend(0.8, 0.9, 0.8, 0.9);
  lHT->SetTextSize(0.04);
  lHT->AddEntry(h1TauPair1HT, "p_{T} > 25GeV");
  lHT->AddEntry(h1TauPair2HT, "p_{T} > 40GeV");
  lHT->Draw();
  c1TauPairHT->Update();

  /***************/
  /***** mT2 *****/
  /***************/
  c1TauPairmT2->cd();
  //
  h1TauPair1mT2->SetLineColor(4);
  h1TauPair1mT2->SetLineWidth(2);
  h1TauPair1mT2->GetXaxis()->SetTitle("mT2");
  h1TauPair1mT2->Draw();
  //
  h1TauPair2mT2->SetLineColor(6);
  h1TauPair2mT2->SetLineWidth(2);
  h1TauPair2mT2->Draw("SAME");
  //
  TLegend* lmT2 = new TLegend(0.8, 0.9, 0.8, 0.9);
  lmT2->SetTextSize(0.04);
  lmT2->AddEntry(h1TauPair1mT2, "p_{T} > 25GeV");
  lmT2->AddEntry(h1TauPair2mT2, "p_{T} > 40GeV");
  lmT2->Draw();
  c1TauPairmT2->Update();
  


  // recoTree1->SetBranchAddress("tau1_E_Reco", &tau1E);
  // recoTree1->SetBranchAddress("tau1_px_reco", &tau1Px);
  // recoTree1->SetBranchAddress("tau1_py_reco", &tau1Py);
  // recoTree1->SetBranchAddress("tau1_pz_reco", &tau1Pz);
  // recoTree1->SetBranchAddress("tau1_pt_reco", &tau1Pt);
  // recoTree1->SetBranchAddress("tau1_dxy_reco", &tau1dXY);
  // recoTree1->SetBranchAddress("tau1_dz_reco", &tau1dZ);
  // recoTree2->SetBranchAddress("tau2_E_Reco", &tau2E);
  // recoTree2->SetBranchAddress("tau2_px_reco", &tau2Px);
  // recoTree2->SetBranchAddress("tau2_py_reco", &tau2Py);
  // recoTree2->SetBranchAddress("tau2_pz_reco", &tau2Pz);
  // recoTree2->SetBranchAddress("tau2_pt_reco", &tau2Pt);
  // recoTree2->SetBranchAddress("tau2_dxy_reco", &tau2dXY);
  // recoTree2->SetBranchAddress("tau2_dz_reco", &tau2dZ);
  // TCanvas* c1TauE = new TCanvas("c1TauE", "c1TauE");
  // TH1D* h1Tau1E = new TH1D("h1Tau1E", "h1Tau1E", 1000, -1000, 20 );
  // TH1D* h1Tau2E = new TH1D("h1Tau2E", "h1Tau2E", 1000, -1000, 20 );
  // TCanvas* c1TauPx = new TCanvas("c1TauPx", "c1TauPx");
  // TH1D* h1Tau1Px = new TH1D("h1Tau1Px", "h1Tau1Px", 1000, -1000, 10);
  // TH1D* h1Tau2Px = new TH1D("h1Tau2Px", "h1Tau2Px", 1000, -1000, 10);
  // TCanvas* c1TauPy = new TCanvas("c1TauPy", "c1TauPy");
  // TH1D* h1Tau1Py = new TH1D("h1Tau1Py", "h1Tau1Py", 1000, -1000, 10);
  // TH1D* h1Tau2Py = new TH1D("h1Tau2Py", "h1Tau2Py", 1000, -1000, 10);
  // TCanvas* c1TauPz = new TCanvas("c1TauPz", "c1TauPz");
  // TH1D* h1Tau1Pz = new TH1D("h1Tau1Pz", "h1Tau1Pz", 1000, -1000, 10);
  // TH1D* h1Tau2Pz = new TH1D("h1Tau2Pz", "h1Tau2Pz", 1000, -1000, 10);
  // TCanvas* c1TaudPt = new TCanvas("c1TaudPt", "c1TaudPt");
  // Th1D* h1Tau1Pt = new TH1D("h1Tau1Pt", "h1Tau1Pt", 1000, 0, 10);
  // Th1D* h1Tau2Pt = new TH1D("h1Tau2Pt", "h1Tau2Pt", 1000, 0, 10);
  //

  theApp->Run(); 
  gSystem->ProcessEvents();
  return 0;
}