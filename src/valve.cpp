#include "valve.h"
#include <math.h>
#define PI 3.1415


    double valve::flowArea(){
      return (PI*0.25*dInner*dInner);
    }

    double valve::flowVolume(){
      return (PI*dInner*pipeLen);
    }

    double valve::getflowIn(double p1, double p2, double opening){//Overriding the method for flow calculation
      if(opening > 1.0)
        opening = 1.0;
      if(opening <0.0)
        opening = 0.0;
      return opening*Cvmax*sqrt(p1-p2);
    }
valve::valve()
{
    //ctor
}

valve::~valve()
{
    //dtor
}
