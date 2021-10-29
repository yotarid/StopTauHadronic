#include "../include/Input.h"


namespace in {

  Input::Input(const std::string& era, const std::string& process, const std::string& channel, bool isSignal, const std::string& dataFilePath) 
    :  era_(era), process_(process), channel_(channel), dataFile_(dataFilePath), dataFilePath_(dataFilePath), isSignal_(isSignal)
  {
    LOG(INFO) << BOLDYELLOW << "\tUsing data file path : " << WHITE << dataFilePath << RESET;
  }

  Input::~Input(){}

  bool Input::Initialise(const std::string& inFilePath)
  {
    recoEvent_ = std::make_shared<in::RecoEvent>();
    genEvent_ = std::make_shared<in::GenEvent>();
    //Input data TFile
    LOG(INFO) << BOLDBLUE << "\t\tOpening input file : " << WHITE << inFilePath << RESET;
    inFilePath_ = inFilePath;
    inFile_ = static_cast<TFile*>(TFile::Open(inFilePath.c_str(), "READ"));
    //Input data TTree
    //RECO
    TTree* recoTree = static_cast<TTree*>(inFile_->Get("miniaodsim2custom/reco"));
    recoEventN_ = recoTree->GetEntries();
    //
    TTree* genTree = static_cast<TTree*>(inFile_->Get("miniaodsim2custom/gen"));
    genEventN_ = genTree->GetEntries();


    //instantiate and initialise reco and gen event handle
    isInitialised_ = recoEvent_->Initialise(recoTree) & genEvent_->Initialise(genTree);

    //Disabling mT2 library copyright message
    asymm_mt2_lester_bisect::disableCopyrightMessage();

    return isInitialised_;
  }

  std::shared_ptr<in::RecoEvent> Input::GetRECOEvent(int iEvent)
  { 
    recoEvent_->LoadEvent(iEvent);
    return recoEvent_;
  }

  std::shared_ptr<in::GenEvent> Input::GetGENEvent(int iEvent)
  { 
    genEvent_->LoadEvent(iEvent);
    return genEvent_;
  }

  void Input::Finalise(void)
  {
    LOG(INFO) << BOLDMAGENTA << "\t\tClosing input file : " << WHITE << inFilePath_ << RESET;
    LOG(INFO) << " " << RESET;
    inFile_->Close();
    isInitialised_ = false;
  }

}//namespace files
