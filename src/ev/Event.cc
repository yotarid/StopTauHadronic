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
    return taus_; 
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