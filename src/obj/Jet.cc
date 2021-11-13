#include "../../include/obj/Jet.h"

namespace obj{

  void Jet::SetIsPfCombinedInclusiveSecondaryVertexV2B(int wpID, bool isPfCISVV2B)
  {
    switch(wpID)
    {
      case 3 : isLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_ = isPfCISVV2B; break;
      case 4 : isMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_ = isPfCISVV2B; break;
      case 5 : isTightPfCombinedInclusiveSecondaryVertexV2BJetTags_ = isPfCISVV2B; break;
      default : throw std::runtime_error("Pf Combined Inclusive Secondary Vertex V2B ID not defined");
    }
  }

  void Jet::SetIsPfDeepFlavour(int wpID, bool isPfDeepFlavour)
  {
    switch(wpID)
    {
      case 3 : isLoosePfDeepFlavourJetTags_ = isPfDeepFlavour; break;
      case 4 : isMediumPfDeepFlavourJetTags_ = isPfDeepFlavour; break;
      case 5 : isTightPfDeepFlavourJetTags_ = isPfDeepFlavour; break;
      default : throw std::runtime_error("Pf Combined Inclusive Secondary Vertex V2B ID not defined");
    }
  }

  bool Jet::isPfCombinedInclusiveSecondaryVertexV2B(int wpID)
  {
    switch(wpID)
    {
      case 3 : return isLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_;
      case 4 : return isMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_;
      case 5 : return isTightPfCombinedInclusiveSecondaryVertexV2BJetTags_;
      default : throw std::runtime_error("Pf Combined Inclusive Secondary Vertex V2B ID not defined");
    }

  }

  bool Jet::isPfDeepFlavour(int wpID)
  {
    switch(wpID)
    {
      case 3 : return isLoosePfDeepFlavourJetTags_;
      case 4 : return isMediumPfDeepFlavourJetTags_;
      case 5 : return isTightPfDeepFlavourJetTags_;
      default : throw std::runtime_error("Pf Combined Inclusive Secondary Vertex V2B ID not defined");
    }
  }
}