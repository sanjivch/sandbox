#include "tank.h"
#define PI 3.1415

double tank::getVolume(double di, double len){
      return PI*di*di*len*0.25;
    }

    double tank::getOpPressure(double inH, double lev){
      return 101.325+ (lev-inH)*1000*9.80665*0.001;
    }

    double tank::levelAccumulated(double dt, double fin, double fout, double h){
      return h+(dt*(fin-fout))/(1000.0*1.5);
    }

    double tank::enthalpyAccumulated(double dt, double fin1, double fin2, double fout, double tankT, double q, double mass, double enthalpy){
      return dt*((fin1*4.187*(40-25) + fin2*4.187*(60-25))-(fout*4.187*(tankT -25))+q)+enthalpy;
    }

    double tank::massAccumulated(double dt, double fin, double fout, double mass){
      return mass + (dt*(fin-fout));
    }

    double* tank::calcComposition(double fin1, double fin2, double massInTank, double port1[], double port2[], double tankC[], double num){

      static double tcomp[3];

      for(int i=0; i<num;i++){
        tcomp[i] = (fin1*port1[i] + fin2*port2[i] + massInTank*tankC[i])/(fin1 + fin2 + massInTank);
      }

      return tcomp;
    }


tank::tank()
{
    //ctor
}

tank::~tank()
{
    //dtor
}
