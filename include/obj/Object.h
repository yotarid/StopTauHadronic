#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <CLHEP/Vector/LorentzVector.h>

namespace obj {
  class Object {
    public :
      explicit Object(){};
      ~Object(){};

      //setters
      void SetE(double E){ E_ = E; };
      
      void SetpX(double pX){ pX_ = pX; };

      void SetpY(double pY){ pY_= pY; };

      void SetpZ(double pZ){ pZ_ = pZ; };

      void SetdXY(double dXY){ dXY_ = dXY; };

      void SetdZ(double dZ){ dZ_ = dZ; };

      //getters
      double GetE(void){ return E_; };

      double GetpX(void){ return pX_; };

      double GetpY(void){ return pY_; };

      double GetpZ(void){ return pZ_; };

      double GetdXY(void){ return dXY_; };

      double GetdZ(void){ return dZ_; };
      
      double GetpT(void){ return std::sqrt( std::pow(pX_,2) + std::pow(pY_,2) ); };

      CLHEP::HepLorentzVector Get4Momentum(void){
        CLHEP::HepLorentzVector fourMomentum;
        fourMomentum.setT(fabs(E_));
        fourMomentum.setX(pX_);
        fourMomentum.setY(pY_);
        fourMomentum.setZ(pZ_);
        return fourMomentum;
      };

    private : 
      double E_;
      double pX_;
      double pY_;
      double pZ_;
      double dXY_;
      double dZ_;
      bool iGenMatched_ = false;
  };
}

#endif