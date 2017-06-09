#include "hxer.h"
#include <math.h>


double hxer::getflowIn(double p1, double p2, double fitr){//Overriding the method for flow calculation

    return fitr*sqrt(p1-p2);
}

double hxer::getOutletTemp(double dt, double fin, double T, double q){
    return T +(dt*q/(fin*4.187));
}

hxer::hxer()
{
    //ctor
}

hxer::~hxer()
{
    //dtor
}
