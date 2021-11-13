#ifndef JET_H
#define JET_H

#include "Object.h"

namespace obj {
  class Jet : public Object {
    public : 
      explicit Jet(){};
      ~Jet(){};

      void SetPartonFlavour(double partonFlavour){
        partonFlavour_ = partonFlavour;
      };
       
      void SetHadronFlavour(double hadronFlavour){
        hadronFlavour_ = hadronFlavour;
      };

      void SetIsISR(bool isISR){
        isISR_ = isISR;
      };

      void SetIsPfCombinedInclusiveSecondaryVertexV2B(int wpID, bool isPfCISVV2B);

      void SetIsPfDeepFlavour(int wpID, bool isPfDeepFlavour);


      double GetPartonFlavour(void){
        return partonFlavour_;
      }

      double GetHadronFlavour(void){
        return hadronFlavour_;
      }

      bool IsISR(void){
        return isISR_;
      }

      bool isPfCombinedInclusiveSecondaryVertexV2B(int wpID);

      bool isPfDeepFlavour(int wpID);

    private :
      double partonFlavour_;
      double hadronFlavour_;
      bool isISR_;
      bool isLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_;
      bool isMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_;
      bool isTightPfCombinedInclusiveSecondaryVertexV2BJetTags_;
      bool isLoosePfDeepFlavourJetTags_;
      bool isMediumPfDeepFlavourJetTags_;
      bool isTightPfDeepFlavourJetTags_;
  };
}

typedef std::vector<std::shared_ptr<obj::Jet>> JetVector;

#endif