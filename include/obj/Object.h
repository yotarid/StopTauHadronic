#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include <CLHEP/Vector/LorentzVector.h>

namespace obj {
  class Object {
    public :
      explicit Object(){};
      ~Object(){};

      //setters
      void SetId(int id){ 
        id_ = id; 
      }

      void SetE(double E){ 
        E_ = E;
      };
      
      void SetpX(double pX){ 
        pX_ = pX;
      };

      void SetpY(double pY){ 
        pY_= pY;
      };

      void SetpZ(double pZ){ 
        pZ_ = pZ;
      };

      void SetdXY(double dXY){ 
        dXY_ = dXY; 
      };

      void SetdZ(double dZ){ 
        dZ_ = dZ; 
      };

      void SetEta(double eta){
        eta_ = eta;
      }

      void SetIsGen(bool isGen){
        isGen_ = isGen;
      }

      void SetIsGenMatched(bool isGenMatched){
        isGenMatched_ = isGenMatched;
      }

      void SetIsUsedToGenMatch(bool isUsedToGenMatch){
        isUsedToGenMatch_ = isUsedToGenMatch;
      }

      //getters
      int GetId(){ 
        return id_; 
      }

      double GetE(void){ 
        return E_; 
      };

      double GetpX(void){ 
        return pX_; 
      };

      double GetpY(void){ 
        return pY_; 
      };

      double GetpZ(void){ 
        return pZ_; 
      };

      double GetdXY(void){ 
        return dXY_; 
      };

      double GetdZ(void){ 
        return dZ_; 
      };

      double GetEta(void){
        return eta_;
      }
      
      double GetpT(void){ 
        return std::sqrt( std::pow(pX_,2) + std::pow(pY_,2) ); 
      };

      CLHEP::HepLorentzVector Get4Momentum(void){
        CLHEP::HepLorentzVector fourMomentum;
        fourMomentum.setT(fabs(E_));
        fourMomentum.setX(pX_);
        fourMomentum.setY(pY_);
        fourMomentum.setZ(pZ_);
        return fourMomentum;
      };

      bool IsGen(void){
        return isGen_;
      }

      bool IsUsedToGenMatch(void){
        return isUsedToGenMatch_;
      }

      bool IsGenMatched(void){
        return isGenMatched_;
      }

    private : 
      int id_;
      bool isGen_ = false;
      bool isUsedToGenMatch_ = false;
      bool isGenMatched_ = false;
      double E_;
      double pX_;
      double pY_;
      double pZ_;
      double dXY_;
      double dZ_;
      double eta_;
  };
}

#endif