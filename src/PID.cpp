#include "PID.h"


double PID::controlPID(double dt, double pv, double sp, double Kc, double Ti, double integral){

      //double error, CO;
      error = pv - sp;
      CO = Kc*error + Kc*integral/Ti;
      return CO/100.0;
    }

    double PID::errorIntegral(double dt, double pv, double sp, double iError){
       return iError+(pv-sp)*dt;
    }
PID::PID()
{
    //ctor
}

PID::~PID()
{
    //dtor
}
