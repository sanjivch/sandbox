#include <iostream>
#include <math.h>
#define PI 3.14
using namespace std;

//Boundary Class
class boundary{
  public:
    double pressureIn;
    double pressureOut;
    
    
};

//PID Controller Class
class PID{
  public: 
    double CO;
};

//Pipe Class
class pipe{
  public:
    double dInner, dOuter;
    double pipeLen;
    
    double getflowIn(){
      return 0;
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

class tank{
  public:
    double diaInner, length, volume;
    double opPressure;
    
    double getVolume(double di, double len){
      return PI*di*di*len*0.25;
    }
    
    double massAccumulated(double dt, double fin, double fout, double h){
      return h+(dt*(fin-fout))/(1000.0*1.5);
    }
  
};


int main()
{
  //cout << "hi\n";
  srand(time(NULL));
  double deltaT = 0.1;
  double flowIn, flowOut, tankLevel =0.0, tankPressure = 101.325;
  
  //Object definitions
  boundary b1, b2;
  valve v1, v2;
  PID pid1, pid2;
  tank t1;
  
  //Object inputs
  v1.dInner = 10.0;
  v1.dOuter = 11.0;
  v1.pipeLen = 2.0;
  v1.Cvmax = 50;
  pid1.CO = 0.5;
  
  v2. Cvmax =25.3;
  pid2.CO = 0.75;
  
  t1.diaInner = 2.1;
  t1.length = 5.0;
  
  t1.volume = t1.getVolume(t1.diaInner, t1.length);
  t1.opPressure = 101.325;
  b1.pressureIn = 120.1; //in kPa
  b2.pressureOut = 101.325;
  
  
  
  
  
  //Object linking and connections
  for(double t=0.0;t<100.0;t+=deltaT){
    flowIn = v1.getflowIn(b1.pressureIn, t1.opPressure, pid1.CO);
    flowOut = v2.getflowIn(tankPressure, b2.pressureOut, pid2.CO);
    tankLevel = t1.massAccumulated(deltaT, flowIn, flowOut, tankLevel);
    tankPressure = 101.325 + (1000*9.80665*tankLevel*0.001);
    cout << flowIn << " " << flowOut<< " "<< tankLevel <<" " << tankPressure<< endl;
    
  }
  
  
}
