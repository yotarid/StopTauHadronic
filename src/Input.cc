#include "../include/Input.h"


namespace in {

  Input::Input(const std::string& era, const std::string& process, const std::string& channel, const std::string& dataFilePath) 
    :  era_(era), process_(process), channel_(channel), dataFile_(dataFilePath), dataFilePath_(dataFilePath)
  {
    recoEvent_ = std::make_unique<in::INRECOEvent>();
    LOG(INFO) << BOLDYELLOW << "\tUsing data file path : " << WHITE << dataFilePath << RESET;
  }

  Input::~Input(){}

  bool Input::Initialise(const std::string& inFilePath)
  {
    //Input data TFile
    LOG(INFO) << BOLDBLUE << "\t\tOpening input file : " << WHITE << inFilePath << RESET;
    inFilePath_ = inFilePath;
    inFile_ = static_cast<TFile*>(TFile::Open(inFilePath.c_str(), "READ"));
    //Input data TTree
    //RECO
    TTree* recoTree = static_cast<TTree*>(inFile_->Get("miniaodsim2custom/reco"));
    recoEventN_ = recoTree->GetEntries();

    //instantiate and initialise reco event handle
    isInitialised_ = recoEvent_->Initialise(recoTree);

    //Disabling mT2 library copyright message
    asymm_mt2_lester_bisect::disableCopyrightMessage();

    return isInitialised_;
  }

  std::shared_ptr<in::INRECOEvent> Input::GetNewRECOEvent(int iEvent)
  { 
    recoEvent_->LoadNewEvent(iEvent);
    return recoEvent_;
  }

  void Input::Finalise(void)
  {
    LOG(INFO) << BOLDMAGENTA << "\t\tClosing input file : " << WHITE << inFilePath_ << RESET;
    LOG(INFO) << " " << RESET;
    inFile_->Close();
    isInitialised_ = false;
  }

}//namespace files
