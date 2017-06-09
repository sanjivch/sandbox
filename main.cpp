/*#include <iostream>
#include "pipe.h"
#include <valve.h>

#include <stdlib.h>

using namespace std;

int main()
{

    pipe p1, p2;
    valve v1;
    PID pid1;

    p1.dInner = 10.0;
    p1.dOuter = 11.0;
    p1.flowIn = 15.0;

    v1.dInner = 9.0;
    v1.dOuter = 10.0;
    v1.presIn = 120.5;
    v1.presOut = 101.3;
    v1.Cvmax = 100.0;

    pid1.PV = p1.flowIn;


    p1.flowOut = p1.flowIn;
    p2.flowIn = p1.flowOut;



    cout << p2.flowIn << " " << p1.getflowIn();
    cout << v1.getflowIn(v1.presIn, v1.presOut, v1.Cvmax);

    //cout << "Thickness" << abs(p1.dInner - p1.dOuter);

    return 0;
}
*/


#include <iostream>
#include <math.h>

#include <composition.h>
#include <boundary.h>
#include "PID.h"
#include "tank.h"
#include "valve.h"
#include "hxer.h"
#include "pump.h"

#define PI 3.14
using namespace std;

/*class composition{//done
  public:
    double z[3];

    double checkSum(){
      double sum = 0.0;
      for(int i = 0; i< 3; i++){
        sum+=z[i];
      }

      if(sum == 1.0)
        return 1.0;
      else
        return -1.0;
    }
};*/


//Boundary Class
/*class boundary: public composition{
  public:
    double pressureIn;
    double temperatureIn;
    double pressureOut;




};*/

//PID Controller Class
/*class PID{
  public:
    double PV, SP, CO;
    double error, Kc=0.5, Ti=2.0, Td;

    double controlPID(double dt, double pv, double sp, double integral){

      error = pv - sp;
      CO = Kc*error + Kc*integral/Ti;
      return CO/100.0;
    }

    double errorIntegral(double dt, double pv, double sp, double iError){
       return iError+(pv-sp)*dt;
    }
};*/

//Pipe Class
/*class pipe: public composition{
  public:
    double dInner, dOuter;
    double pipeLen;

    double tempIn, tempOut, tempAvg;

    double getflowIn(){
      return 0;
    }

};*/

//Valve inherits Pipe class
/*class valve : public pipe{
  public:
    double Cvmax;

    double flowArea(){
      return (PI*0.25*dInner*dInner);
    }

    double flowVolume(){
      return (PI*dInner*pipeLen);
    }

    double getflowIn(double p1, double p2, double opening){//Overriding the method for flow calculation
      if(opening > 1.0)
        opening = 1.0;
      if(opening <0.0)
        opening = 0.0;
      return opening*Cvmax*sqrt(p1-p2);
    }



};*/

/*class heatxch : public pipe{
  public:
      double fitRes;
      double heatDuty;
      double Tin, TOut;

      double getflowIn(double p1, double p2, double fitr){//Overriding the method for flow calculation

      return fitr*sqrt(p1-p2);
      }

      double getOutletTemp(double dt, double fin, double T, double q){
        return T +(dt*q/(fin*4.187));
      }


};*/

/*class pump : public pipe{
  public:

      int runFlag; //0 = Stop; 1= Run
      double a0, a1, a2; //Pump curve coefficients
      double speed;


      double getflowIn(double p1, double p2, double a, double b, double c, double ns, int flag){
        if(flag != 0 ){
          b*= ns;
          c*= ns*ns;

        return (-b - sqrt(b*b-(4*a*(c-(p1-p2)))))/(2*a);// Affinity laws

        }

        return 100*sqrt(p1-p2);

      }

      double getPowerConsumed(){
        return 0;
      }

};*/

/*class tank: public composition{
  public:
    double diaInner, length, volume;
    double opPressure;
    double heatIn;

    double portInHeight, portOutHeight;//in absolute terms from the bottom of the tank [m]
    double portInHeight2;

    double getVolume(double di, double len){
      return PI*di*di*len*0.25;
    }

    double getOpPressure(double inH, double lev){
      return 101.325+ (lev-inH)*1000*9.80665*0.001;
    }

    double levelAccumulated(double dt, double fin, double fout, double h){
      return h+(dt*(fin-fout))/(1000.0*1.5);
    }

    double enthalpyAccumulated(double dt, double fin1, double fin2, double fout, double tankT, double q, double mass, double enthalpy){
      return dt*((fin1*4.187*(40-25) + fin2*4.187*(60-25))-(fout*4.187*(tankT -25))+q)+enthalpy;
    }

    double massAccumulated(double dt, double fin, double fout, double mass){
      return mass + (dt*(fin-fout));
    }

    double *calcComposition(double fin1, double fin2, double massInTank, double port1[], double port2[], double tankC[], double num){

      static double tcomp[3];

      for(int i=0; i<num;i++){
        tcomp[i] = (fin1*port1[i] + fin2*port2[i] + massInTank*tankC[i])/(fin1 + fin2 + massInTank);
      }

      return tcomp;
    }

};*/


int main()
{

  double deltaT = 0.1;
  double flowIn = 0.0, flowOut = 0.0, tankLevel = 0.0, tankPressure = 101.325, tankTemperature = 25.0, mass = 0.0, enthalpyIn = 0.0;

  double flowIn1 =0.0, flowIn2 = 0.0, flowIn3 = 0.0, flowIn4 = 0.0;

  double intError = 0.0, intError2 = 0.0;

  double head = 165.9;

  double *tankComp;

  //Object definitions
  boundary b1, b2, b3, b4, b5;
  valve v1, v2, v3;
  PID pid1, pid2;
  tank t1;
  hxer h1;
  pump pu1;

  //Object inputs
  v1.dInner = 10.0;
  v1.dOuter = 11.0;
  v1.pipeLen = 2.0;
  v1.Cvmax = 50.0;
  pid1.CO = 0.5;

  v2.Cvmax =55.3;
  pid2.CO = 0.75;

  v3.Cvmax = 40.0;

  t1.diaInner = 2.1;
  t1.length = 5.0;

  t1.portInHeight = 3.1;
  t1.portInHeight2 = 3.2;
  t1.portOutHeight = 0.5;

  t1.z[0] = 1.0;
  t1.z[1] = 0.0;
  t1.z[2] = 0.0;



  t1.heatIn = -100.0;



  t1.volume = t1.getVolume(t1.diaInner, t1.length);
  //t1.opPressure = t1.getOpPressure();
  pu1.speed = 0.95;
  pu1.a0 = -0.002587798;
  pu1.a1 = -0.036577381;
  pu1.a2 = 165.9125;
  pu1.runFlag = 0;

  b1.pressureIn = 120.1; //in kPa
  b2.pressureOut = 101.325;

  b1.temperatureIn = 40.0;
  b1.z[0] = 0.2;
  b1.z[1] = 0.5;
  b1.z[2] = 0.3;

//  cout << b1.checkSum()<< endl;


  pid1.SP = 105.0;
  pid2.SP = 2.0;

  pid1.Kc = -0.25;
  pid1.Ti = 1.0;
  pid2.Kc = 0.5;
  pid2.Ti = 2.0;

  b3.pressureIn = 150.0;
  b3.temperatureIn = 50.0;



  b4.pressureOut = 120.0;

  b5.pressureIn = 125.6;
  b5.temperatureIn = 60.0;

  b5.z[0] = 0.5;
  b5.z[1] = 0.1;
  b5.z[2] = 0.4;

//  cout << b5.checkSum()<<endl;

  h1.fitRes =100.0;
  h1.heatDuty = 100.0;

  h1.Tin = h1.TOut = b3.temperatureIn;  //Initial exit temperature of the hxer


  //Object linking and connections
  for(double t=0.0;t<1500.0;t+=deltaT){

    flowIn1 = v1.getflowIn(b1.pressureIn, t1.getOpPressure(t1.portInHeight, tankLevel), pid1.controlPID(deltaT,flowIn, pid1.SP, pid1.Kc, pid1.Ti, intError2));
    flowIn3 = v3.getflowIn(b5.pressureIn,t1.getOpPressure(t1.portInHeight2, tankLevel),0.5);
    flowIn = flowIn1 + flowIn3;

    v1.z[0] = b1.z[0];
    v1.z[1] = b1.z[1];
    v1.z[2] = b1.z[2];

    v3.z[0] = b5.z[0];
    v3.z[1] = b5.z[1];
    v3.z[2] = b5.z[2];

    v1.tempIn = v1. tempOut = b1.temperatureIn;
    tankLevel = t1.levelAccumulated(deltaT, flowIn, flowOut, tankLevel);
    tankPressure = 101.325 + (1000*9.80665*tankLevel*0.001);

    mass = t1.massAccumulated(deltaT,flowIn, flowOut, mass);
    enthalpyIn = t1.enthalpyAccumulated(deltaT, flowIn1,flowIn3, flowOut, tankTemperature, t1.heatIn, mass, enthalpyIn);
    tankTemperature = 25 + enthalpyIn/(mass*4.187); //25 is reference temperature for enthalpy calculation
    tankComp = t1.calcComposition(flowIn1, flowIn3,mass,v1.z,v3.z,t1.z,3);

    flowOut = v2.getflowIn(tankPressure, b2.pressureOut, pid2.controlPID(deltaT,tankLevel, pid2.SP, pid2.Kc, pid2.Ti, intError));
   // v2.tempIn = v2.tempOut = tankTemperature;

    intError = pid2.errorIntegral(deltaT, tankLevel, pid2.SP, intError);
    intError2 = pid1.errorIntegral(deltaT, flowIn, pid1.SP, intError2);

    flowIn2 = h1.getflowIn(b3.pressureIn, b4.pressureOut, h1.fitRes);

    h1.TOut = h1.getOutletTemp(deltaT,flowIn2,h1.TOut,h1.heatDuty);

    head-=0.01;
    if(head < 110.0)
      head = 110.0;

    flowIn4 = pu1.getflowIn(head, 0.01, pu1.a0, pu1.a1, pu1.a2, pu1.speed, pu1.runFlag);

    for(int i=0;  i<3; i++){

      t1.z[i] =  *(tankComp + i);
      cout << t1.z[i]<< " ";
    }
    //cout<< endl;
    //cout << t << " " << flowIn2 << " " <<h1.TOut<<endl;

    cout << flowIn1<<" "<<flowIn3 << " " << flowOut<< " "<< tankLevel <<" " << tankPressure<< " "<<tankTemperature<<" "<<pid2.CO<<  endl;
    //cout << enthalpyIn << " " << tankTemperature  << endl;

    //cout <<head << " "<< flowIn4<< endl;

  }


}
