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
    eventWrapper_ = std::make_shared<in::EventWrapper>();
    //Input data TFile
    LOG(INFO) << BOLDBLUE << "\t\tOpening input file : " << WHITE << inFilePath << RESET;
    inFilePath_ = inFilePath;
    inFile_ = static_cast<TFile*>(TFile::Open(inFilePath.c_str(), "READ"));

    isInitialised_ = eventWrapper_->Initialise(inFile_); 

    //Disabling mT2 library copyright message
    asymm_mt2_lester_bisect::disableCopyrightMessage();

    return isInitialised_;
  }

  void Input::Finalise(void)
  {
    LOG(INFO) << BOLDMAGENTA << "\t\tClosing input file : " << WHITE << inFilePath_ << RESET;
    LOG(INFO) << " " << RESET;
    inFile_->Close();
    isInitialised_ = false;
  }

  std::ifstream& Input::GetDataFile(void)
  { 
    return dataFile_; 
  }

  std::string Input::GetDataFilePath(void)
  { 
    return dataFilePath_; 
  }

  TFile* Input::GetInputFile(void)
  { 
    return inFile_; 
  }

  std::string Input::GetInputFilePath(void)
  { 
    return inFilePath_; 
  }

  std::shared_ptr<in::EventWrapper> Input::GetEventWrapper(void)
  {
    return eventWrapper_;
  }
}//namespace files
