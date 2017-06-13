#include <iostream>
#include <math.h>
#define PI 3.14
using namespace std;

class composition{
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
    
    double getMolWeight(){
      double MW = 0.0;
      for(int i=0; i< 3; i++){
        MW += z[i]*1;//"1" should be replaced by the MW of the compound
      }
      
      return 0;
    }
};


//Boundary Class
class boundary: public composition{
  public:
    double pressureIn;
    double temperatureIn;
    double pressureOut;
    double density;
    double elevation;
    
    
    
    double effectivePressure(double p, double el){
      return (p + el*1000*9.80665/1000);
    }


};

//PID Controller Class
class PID{
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
};

//Pipe Class
class pipe: public composition{
  public:
    double dInner, dOuter;
    double pipeLen;
    
    double tempIn, tempOut, tempAvg;

    double getflowIn(double p1, double p2, double k){
      return k*sqrt(p1-p2);
    }

};

//Valve inherits Pipe class
class valve : public pipe{
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



};

class heatxch : public pipe{
  public:
      double fitRes;
      double heatDuty;
      double Tin, TOut;
      
      double hxArea;
      double U;
      
      double getflowIn(double p1, double p2, double fitr){//Overriding the method for flow calculation
      if(fitr <0.0)
        fitr = 0.0;
      
      return fitr*sqrt(p1-p2);
      }
      
      double getOutletTemp(double dt, double fin, double T, double q){
       if(fin <= 0.0)
        return T;
       else
        return T +(dt*q/(fin*4.187));
      }
      
      double getLMTD(double Thot1, double Thot2, double Tcold1, double Tcold2){
        return ((Thot1 - Tcold1)-(Thot2 - Tcold2))/log((Thot1 - Tcold1)/(Thot2 - Tcold2));
      }
    

};

class pump : public pipe{
  public:
      
      int runFlag; //0 = Stop; 1= Run
      double a0, a1, a2; //Pump curve coefficients
      double speed;
      
      double suctionPressure, dischargePressure;
      
      
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
      
};

class tank: public composition{
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

};

class node : public boundary{
  public:
    
    
    double initPressure, initTemperature;
    double massIn, massOut;
    
    double getPressure(double m1, double m2, double nodeP){
      double error = abs(m1-m2);
      if(error <= 0.001)
        return nodeP;
      else
      {
        
          
          nodeP+=error*10;
          
          
        
      return 0;
      }  
    }
  
};

class slider{
  public:
    double pos;
  
};


int main()
{
  
  double deltaT = 0.1;
  double flowIn = 0.0, flowOut = 0.0, tankLevel = 0.0, tankPressure = 101.325, tankTemperature = 25.0, mass = 0.0, enthalpyIn = 0.0;
  
  double flowIn1 =0.0, flowIn2 = 0.0, flowIn3 = 0.0, flowIn4 = 0.0, flowIn5 = 0.0, flowIn6 = 0.0;

  double intError = 0.0, intError2 = 0.0, intError3 = 0.0;
  
  double head = 165.9;
  
  double *tankComp;

  //Object definitions
  boundary b1, b2, b3, b4, b5, b6, b7;
  valve v1, v2, v3, v4;
  pipe pip1;
  PID pid1, pid2, pid3;
  tank t1;
  heatxch h1, h2;
  pump pu1;
  node n1;
  slider sl1, sl2;

  //Object inputs
  v1.dInner = 10.0;
  v1.dOuter = 11.0;
  v1.pipeLen = 2.0;
  v1.Cvmax = 50.0;
  pid1.CO = 0.5;

  v2.Cvmax =55.3;
  pid2.CO = 0.75;
  
  v3.Cvmax = 20.0;
  
  v4.Cvmax = 40.0;

  t1.diaInner = 2.1;
  t1.length = 5.0;

  t1.portInHeight = 3.1;
  t1.portInHeight2 = 3.2;
  t1.portOutHeight = 0.5;
  
  t1.z[0] = 1.0;
  t1.z[1] = 0.0;
  t1.z[2] = 0.0;
  
  

  t1.heatIn = 100.0;
  
  

  t1.volume = t1.getVolume(t1.diaInner, t1.length);
  //t1.opPressure = t1.getOpPressure();
  pu1.speed = 0.95;
  pu1.a0 = -0.002587798;
  pu1.a1 = -0.036577381;
  pu1.a2 = 165.9125;
  pu1.runFlag = 0;
  
  b1.pressureIn = 120.1; //in kPa
  b2.pressureOut = 101.325;
  
  b1.elevation = 5.0;// in [m]
  
  b1.temperatureIn = 40.0;
  b1.z[0] = 0.2;
  b1.z[1] = 0.5;
  b1.z[2] = 0.3;
  
  cout << b1.checkSum()<< endl;
  

  pid1.SP = 105.0;
  pid2.SP = 2.0;
  pid3.SP = 85.0;

  pid1.Kc = -0.15;
  pid1.Ti = 1.0;
  pid2.Kc = 0.5;
  pid2.Ti = 2.0;
  pid3.Kc = 1.0;
  pid3.Ti = 2.1;
  
  b3.pressureIn = 150.0;
  b3.temperatureIn = 50.0;
  
 
  
  b4.pressureOut = 120.0;
  
  b5.pressureIn = 125.6;
  b5.temperatureIn = 60.0;
  
  b5.z[0] = 0.5;
  b5.z[1] = 0.1;
  b5.z[2] = 0.4;
  
  cout << b5.checkSum()<<endl;
  
  
  b6.pressureIn = 110.0;
  b6.temperatureIn = 90.0;
  b6.elevation = 5.0;
  
  b6.z[0] = 1.0;
  b6.z[1] = 0.0;
  b6.z[2] = 0.0;
  
  b7.pressureOut = 105.0;
  b7.elevation = 3.6;
  
  sl1.pos = 0.0;
  
  n1.initPressure = 101.325;
  
  h1.fitRes =10.0;
  h1.heatDuty = 0;//Changed from 100.0 
  
  h2.fitRes = 90.0;
  h2.hxArea = 2.0;
  h2.U = 0.01;//in [kW/m^2. K]
  
  h1.Tin = h1.TOut = b3.temperatureIn;  //Initial exit temperature of the hxer 
  h2.Tin = b6.temperatureIn;
  h2.TOut = h2.Tin - 0.05;
  

  //Object linking and connections
  for(double t=0.0;t<2500.0;t+=deltaT){
    flowIn1 = v1.getflowIn(b1.effectivePressure(b1.pressureIn,b1.elevation), t1.getOpPressure(t1.portInHeight, tankLevel), pid1.controlPID(deltaT,flowIn, pid1.SP, intError2));
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
    
    flowOut = v2.getflowIn(tankPressure, b2.pressureOut, pid2.controlPID(deltaT,tankLevel, pid2.SP, intError));
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
      //cout << t1.z[i]<< " ";
    }
    //cout<< endl;
    //cout << t << " " << flowIn2 << " " <<h1.TOut<<endl;

    //cout << flowIn1<<" "<<flowIn3 << " " << flowOut<< " "<< tankLevel <<" " << tankPressure<< " "<<tankTemperature<<" "<<pid2.CO<<  endl;
    //cout << enthalpyIn << " " << tankTemperature  << endl;
    
    //cout <<head << " "<< flowIn4<< endl;
    
   // flowIn5 = v4.getflowIn(b6.effectivePressure(b6.pressureIn, b6.elevation), b7.effectivePressure(b7.pressureOut, b7.elevation), sl1.pos);
   flowIn5 = h2.getflowIn(b6.pressureIn,b7.pressureOut,pid3.controlPID(deltaT,h2.TOut,pid3.SP,intError3));
   intError3 = pid3.errorIntegral(deltaT,h2.TOut,pid3.SP,intError3);
   h2.heatDuty = -h2.U * h2.hxArea * h2.getLMTD(h2.Tin, h2.TOut,h1.Tin, h1.TOut);
   
   h2.TOut = h2.getOutletTemp(deltaT, flowIn5, h2.TOut, h2.heatDuty);
   h1.heatDuty = -h2.heatDuty;
   
    cout << flowIn5 << " " <<h1.Tin <<" "<< h1.TOut <<" "<< h2.Tin <<" "<< h2.TOut<<" "<<h1.heatDuty<<" "<<h2.heatDuty<< endl;
    //sl1.pos+= 0.01;
    
    //n1.effectivePressure()

  }


}
