#include "../include/ev/Event.h"

namespace in {

  Event::Event(){}

  Event::~Event(){}

  Event& Event::operator=(Event&& other)
  {
    if(tree_)
    {
      delete tree_;
    }
    tree_ = other.tree_;
    other.tree_ = nullptr;
    return *this;
  }

  bool Event::LoadEvent(int iEvent)
  {
    if( tree_->GetEntry(iEvent) == -1){
      return false;
    }else{
      LoadTaus();
      eventN_ = iEvent;
      return true;  
    }
  }

  bool Event::IsInitialised(void)
  { 
    return isInitialised_; 
  }

  TTree* Event::GetTree(void)
  { 
    return tree_; 
  }

  int Event::GetEventN(void)
  {
    return eventN_; 
  }

  TauVector Event::GetTaus(void)
  { 
    return std::move(taus_); 
  }

  double Event::GetMETE(void)
  { 
    return METE_; 
  }

  double Event::GetMETPhi(void)
  { 
    return METPhi_; 
  }
}