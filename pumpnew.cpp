#include <iostream>
#include <math.h>

#define PI 3.1415
#define g 9.80665
using namespace std;

int main(){
  
  double diaIn, diaOut, inletPr, outletPr, inletEl, outletEl, pipeLen, epsilon, rho, viscosity;
  double mdot;
  double area, vel, NRe, f = 0.00, kFit = 0.4;
  double actHead;
  double massFlow,suctionPr, pumpPr,delPPipe, delPPump, volFlow;
  
  cin >> diaIn>> diaOut>>inletPr>> outletPr>> inletEl>> outletEl>> pipeLen>> epsilon>> rho>> viscosity;
  
  //Calculations
  for(int i =1; i<10; i++){
  area = 0.25*PI*pow(0.001*diaIn,2);
  
  massFlow = area * sqrt((2*rho*abs(outletPr - inletPr))/(f*pipeLen*1000/diaIn + kFit));
  vel = massFlow/(rho*area);
  NRe = 0.001*diaIn * vel * rho/ viscosity;
  
  if(NRe > 2100.0)
    f = 1.325/pow(log(epsilon/(3.7*diaIn) + 5.74/pow(NRe,0.9)),2);
  else
    f = 16.0/NRe;
    
    cout << i << endl;
  
  
  
  actHead = outletPr + rho*g*(outletEl-inletEl)*0.001;
  
  suctionPr = inletPr;
  delPPipe = pow(massFlow/area,2)*(f*pipeLen*1000.0/diaIn + kFit)/(2*rho)/1000.0; 
  pumpPr = suctionPr - delPPipe;
  delPPump = actHead - pumpPr;
  
  cout << "Area: "<<area << " m2" <<endl;
  cout << "Mass flow: " << massFlow << " kg/s" << endl;
  cout << "Velocity: " << vel << " m/s" << endl;
  cout << "Reynolds No.: " << NRe << endl;
  cout << "Friction factor: "<< f <<endl;
  cout << "Actual head: "<<actHead <<" kPa"<<endl;
  cout << "Pipe dP: "<<delPPipe<< " kPa"<<endl;
  cout << "Pump Pr: "<<pumpPr<<" kPa"<<endl;
  cout << "TDH: "<<delPPump<<" kPa"<<endl;
  }
  
}
