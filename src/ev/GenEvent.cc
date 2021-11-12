#include "../include/ev/GenEvent.h"

namespace in {
  GenEvent::GenEvent(){}

  GenEvent::~GenEvent(){}

  GenEvent& GenEvent::operator=(GenEvent&& other)
  {
    if(tree_)
    {
      delete tree_;
    }
    tree_ = other.tree_;
    other.tree_ = nullptr;
    return *this;
  }

  bool GenEvent::Initialise(TTree* tree)
  {
    if(tree == nullptr) throw std::runtime_error(std::string("ERROR : Input GEN tree is nullptr"));

    eventN_ = tree->GetEntries();

    tree->SetBranchAddress("stop1_m_genParam", &stopMGenParam_);
    tree->SetBranchAddress("neutralino1_m_genParam", &neutralinoMGenParam_);
    tree->SetBranchAddress("outgoingParton_n_gen", &outgoingPartonNGen_);
    tree->SetBranchAddress("scaleWeight_1", &scaleWeight1_);
    tree->SetBranchAddress("scaleWeight_2", &scaleWeight2_);
    tree->SetBranchAddress("scaleWeight_3", &scaleWeight3_);
    tree->SetBranchAddress("scaleWeight_4", &scaleWeight4_);
    tree->SetBranchAddress("scaleWeight_5", &scaleWeight5_);
    tree->SetBranchAddress("scaleWeight_6", &scaleWeight6_);
    tree->SetBranchAddress("scaleWeight_7", &scaleWeight7_);
    tree->SetBranchAddress("scaleWeight_8", &scaleWeight8_);
    tree->SetBranchAddress("scaleWeight_9", &scaleWeight9_);

    tree->SetBranchAddress("el_n_gen", &elN_);
    tree->SetBranchAddress("el_E_gen", &elEVector_);
    tree->SetBranchAddress("el_px_gen", &elPxVector_);
    tree->SetBranchAddress("el_py_gen", &elPyVector_);
    tree->SetBranchAddress("el_pz_gen", &elPzVector_);
    tree->SetBranchAddress("el_isPrompt_gen", &elIsPromptVector_);

    tree->SetBranchAddress("mu_n_gen", &muN_);
    tree->SetBranchAddress("mu_E_gen", &muEVector_);
    tree->SetBranchAddress("mu_px_gen", &muPxVector_);
    tree->SetBranchAddress("mu_py_gen", &muPyVector_);
    tree->SetBranchAddress("mu_pz_gen", &muPzVector_);
    tree->SetBranchAddress("mu_isPrompt_gen", &muIsPromptVector_);

    tree->SetBranchAddress("tau_E_gen", &tauEVector_);
    tree->SetBranchAddress("tau_px_gen", &tauPxVector_);
    tree->SetBranchAddress("tau_py_gen", &tauPyVector_);
    tree->SetBranchAddress("tau_pz_gen", &tauPzVector_);
    tree->SetBranchAddress("tau_vis_n_gen", &tauVisN_);
    tree->SetBranchAddress("tau_vis_E_gen", &tauVisEVector_);
    tree->SetBranchAddress("tau_vis_px_gen", &tauVisPxVector_);
    tree->SetBranchAddress("tau_vis_py_gen", &tauVisPyVector_);
    tree->SetBranchAddress("tau_vis_pz_gen", &tauVisPzVector_);
    tree->SetBranchAddress("tau_isPrompt_gen", &tauIsPromptVector_);

    tree->SetBranchAddress("t_n_gen", &tQuarkN_);
    tree->SetBranchAddress("t_E_gen", &tQuarkEVector_);
    tree->SetBranchAddress("t_px_gen", &tQuarkPxVector_);
    tree->SetBranchAddress("t_py_gen", &tQuarkPyVector_);
    tree->SetBranchAddress("t_pz_gen", &tQuarkPzVector_);

    tree->SetBranchAddress("b_n_gen", &bQuarkN_);
    tree->SetBranchAddress("b_E_gen", &bQuarkEVector_);
    tree->SetBranchAddress("b_px_gen", &bQuarkPxVector_);
    tree->SetBranchAddress("b_py_gen", &bQuarkPyVector_);
    tree->SetBranchAddress("b_pz_gen", &bQuarkPzVector_);

    tree->SetBranchAddress("W_n_gen", &wBosonN_);
    tree->SetBranchAddress("W_E_gen", &wBosonEVector_);
    tree->SetBranchAddress("W_px_gen", &wBosonPxVector_);
    tree->SetBranchAddress("W_py_gen", &wBosonPyVector_);
    tree->SetBranchAddress("W_pz_gen", &wBosonPzVector_);

    tree->SetBranchAddress("Z_n_gen", &zBosonN_);
    tree->SetBranchAddress("Z_E_gen", &zBosonEVector_);
    tree->SetBranchAddress("Z_px_gen", &zBosonPxVector_);
    tree->SetBranchAddress("Z_py_gen", &zBosonPyVector_);
    tree->SetBranchAddress("Z_pz_gen", &zBosonPzVector_);

    tree->SetBranchAddress("stau1_n_gen", &stauN_);
    tree->SetBranchAddress("stau1_E_gen", &stauEVector_);
    tree->SetBranchAddress("stau1_px_gen", &stauPxVector_);
    tree->SetBranchAddress("stau1_py_gen", &stauPyVector_);
    tree->SetBranchAddress("stau1_pz_gen", &stauPzVector_);

    tree->SetBranchAddress("stop1_n_gen", &stopN_);
    tree->SetBranchAddress("stop1_E_gen", &stopEVector_);
    tree->SetBranchAddress("stop1_px_gen", &stopPxVector_);
    tree->SetBranchAddress("stop1_py_gen", &stopPyVector_);
    tree->SetBranchAddress("stop1_pz_gen", &stopPzVector_);

    tree->SetBranchAddress("chargino1_n_gen", &charginoN_);
    tree->SetBranchAddress("chargino1_E_gen", &charginoEVector_);
    tree->SetBranchAddress("chargino1_px_gen", &charginoPxVector_);
    tree->SetBranchAddress("chargino1_py_gen", &charginoPyVector_);
    tree->SetBranchAddress("chargino1_pz_gen", &charginoPzVector_);

    tree->SetBranchAddress("jet_n_gen", &jetN_);
    tree->SetBranchAddress("jet_E_gen", &jetEVector_);
    tree->SetBranchAddress("jet_px_gen", &jetPxVector_);
    tree->SetBranchAddress("jet_py_gen", &jetPyVector_);
    tree->SetBranchAddress("jet_pz_gen", &jetPzVector_);

    tree->SetBranchAddress("METFixEE2017_E_gen", &METE_);
    tree->SetBranchAddress("METFixEE2017_phi_gen", &METPhi_);

    LOG(INFO) << BOLDBLUE << "\tInitialised input GEN event " << RESET;
    tree_ = tree;
    isInitialised_ = true;

    return isInitialised_;
  }

  bool GenEvent::LoadEvent(int iEvent)
  {
    if( tree_->GetEntry(iEvent) == -1){
      return false;
    }else{
      LoadTaus();
      LoadVisibleTaus();
      eventN_ = iEvent;
      return true;  
    }
  }

  void GenEvent::LoadTaus(void)
  {
    //Load Tau objetcs
    taus_.clear();
    int tauN = tauEVector_->size();
    for(int iTau = 0; iTau < tauN; iTau++)
    {
      // if(tauN < 1) break;
      std::shared_ptr<obj::Tau> tau = std::make_shared<obj::Tau>();
      tau->SetIsGen(true);
      tau->SetId(iTau);
      //set kinematics
      tau->SetE(tauEVector_->at(iTau));
      tau->SetpX(tauPxVector_->at(iTau));
      tau->SetpY(tauPyVector_->at(iTau));
      tau->SetpZ(tauPzVector_->at(iTau));
      tau->SetEta(fabs(tau->Get4Momentum().eta()));
      //push back
      taus_.push_back(tau);
    }
  }

  void GenEvent::LoadVisibleTaus(void)
  {
    //Load Tau objetcs
    visibleTaus_.clear();
    for(int iTau = 0; iTau < tauVisN_; iTau++)
    {
      // if(tauN < 1) break;
      std::shared_ptr<obj::Tau> tau = std::make_shared<obj::Tau>();
      tau->SetIsGen(true);
      tau->SetIsPrompt(tauIsPromptVector_->at(iTau));
      tau->SetId(iTau);
      //set kinematics
      tau->SetE(tauVisEVector_->at(iTau));
      tau->SetpX(tauVisPxVector_->at(iTau));
      tau->SetpY(tauVisPyVector_->at(iTau));
      tau->SetpZ(tauVisPzVector_->at(iTau));
      tau->SetEta(fabs(tau->Get4Momentum().eta()));
      //push back
      visibleTaus_.push_back(tau);
    }
  }
}