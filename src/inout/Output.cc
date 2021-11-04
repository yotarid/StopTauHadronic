#include "../include/inout/Output.h"

namespace out {

  Output::Output(const std::string& era, const std::string& process, const std::string& channel)
    : era_(era), process_(process), channel_(channel)
  {
    LOG(INFO) << "" << RESET;
    LOG(INFO) << BOLDGREEN << "Era : " << WHITE << era << BOLDGREEN << ", Process : " << WHITE << process << BOLDGREEN << ", Channel : " << WHITE << channel << RESET;
  }

  Output::~Output()
  {
    //LOG(INFO) << BOLDYELLOW << "\t\tClosing output file : " << WHITE << outFilePath_ << RESET;
    outFile_->Close();
  }

  bool Output::Initialise(const std::string& outFileName)
  {
    event_ = std::make_shared<out::OutEvent>();
    std::string outDirPath = Form("%s/%s/%s/%s", std::getenv("SAMPLEPRODUCTION_OUT_DIR"), era_.c_str(), process_.c_str(), channel_.c_str());
    LOG(INFO) << BOLDYELLOW << "\tCreating output directory : " << WHITE << outDirPath << RESET;
    system(Form("mkdir -p %s", outDirPath.c_str()));

    LOG(INFO) << BOLDYELLOW << "\t\tCreating output file : " << WHITE << Form("%s/%s.root", outDirPath.c_str(), outFileName.c_str()) << RESET;
    outFile_ = static_cast<TFile*>(TFile::Open(Form("%s/%s.root", outDirPath.c_str(), outFileName.c_str()), "RECREATE"));
    outFilePath_ = outDirPath + "/" + outFileName;
    if(!outFile_)
      throw std::runtime_error("Output:Output : ROOT File is nullptr");
    //
    LOG(INFO) << BOLDYELLOW << "\t\t\tCreating ROOT directory : " << WHITE << "miniaodsim2custom2custom" << RESET;
    outROOTDir_ = static_cast<TDirectory*>(outFile_->mkdir("miniaodsim2custom2custom"));
    if(!outROOTDir_)
      throw std::runtime_error("Output:Output : ROOT Directory is nullptr");
    outROOTDir_->cd();
    //
    TTree* tree = new TTree("skimmed", "Selection of reconstructed events");
    isInitialised_ = event_->Initialise(tree);

    return isInitialised_;
  }

  void Output::Finalise(void)
  {
    //LOG(INFO) << BOLDMAGENTA << "\t Closing output file : " << WHITE << outFilePath_ << RESET;
    LOG(INFO) << " " << RESET;
    outFile_->Write();
    outFile_->Close();
    isInitialised_ = false;
  }
}//namespace out
