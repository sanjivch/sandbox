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
int main()
{
  //cout << "hi\n";
  
  boundary b1, b2;
  valve v1;
  PID pid1;
  v1.dInner = 10.0;
  v1.dOuter = 11.0;
  v1.pipeLen = 2.0;
  v1.Cvmax = 100;
  pid1.CO = -1.5;
  b1.pressureIn = 120.1; //in kPa
  b2.pressureOut = 105.8;
  
  cout << v1.flowArea()<< " " << v1.flowVolume()<< " "<< v1.getflowIn(b1.pressureIn, b2.pressureOut, pid1.CO) << endl;
  
}
