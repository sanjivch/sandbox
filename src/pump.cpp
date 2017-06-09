#include "pump.h"
#include <math.h>

double pump::getflowIn(double p1, double p2, double a, double b, double c, double ns, int flag){
        if(flag != 0 ){
          b*= ns;
          c*= ns*ns;

        return (-b - sqrt(b*b-(4*a*(c-(p1-p2)))))/(2*a);// Affinity laws

        }

    return 100*sqrt(p1-p2);
}

double pump::getPowerConsumed(){
        return 0;
}


pump::pump()
{
    //ctor
}

pump::~pump()
{
    //dtor
}
