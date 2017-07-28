#include <iostream>
#include <math.h>
using namespace std;

int main(){
  /* 
     Karra Model for the Screen
  
     dw = diameter of the wire
     h = 
     hT = effective throughfall aperture of the screen
     theta = angle of inclination of the deck
     
  */
  int S;
  double A, B, C, D, E, F, Gc, T, adj_A;
  double h, dw, theta;
  double hT, openArea;//hT in mm; A in metric tons/ hr m^2
  double overFracFeed, overHalfFracFeed, Xn, rhoBulk, screenArea;
  
  cin >> h >> dw >> theta;
  hT = (h + dw)*cos(theta) - dw;
  
  //=========================
  //A : The basic capacity
  //=========================
  
  if(hT < 51.0)
    A = 12.13*pow(hT, 0.32) - 10.3;
  else
    A = 0.34*hT + 14.41;
  
  openArea = 21.5*log(h) + 37;
  
  //===========================
  //B : The oversize factor 
  //===========================
  if(overFracFeed <= 0.87)
    B = 1.6 - 1.2*overFracFeed;
  else
    B = 4.275 - 4.25*overFracFeed; 
  
  //===========================
  //C : The half-size factor 
  //===========================
  
  if(overHalfFracFeed <= 0.3)
    C = 0.7 + 1.2*overHalfFracFeed;
  else if(overHalfFracFeed > 0.3 && overHalfFracFeed <= 0.55)
    C = 2.053*pow(overHalfFracFeed, 0.564);
  else if(overHalfFracFeed > 0.55 && overHalfFracFeed <= 0.8)
    C = 3.35*pow(overHalfFracFeed, 1.37);
  else
    C = 5.0*overHalfFracFeed - 1.5;
    
  //============================
  //D : The deck location factor 
  //============================
  
  D = 1.1 - 0.1*S;  //S=1 for top deck; S=2 for 2nd deck and so on...
  //============================
  //E : The wet screening factor 
  //============================
  T = 1.26*hT;
  
  if(T < 1.0)
    E = 1.0;
  else if(T >= 1.0 && T < 2.0)
    E = T;
  else if(T >= 2.0 && T < 4.0)
    E = 1.5 + 0.25*T;
  else if(T >= 4.0 && T < 6.0)
    E = 2.5;
  else if(T >= 6.0 && T < 10.0)
    E = 3.25 - 0.125*T;
  else if(T >= 10.0 && T < 12.0)
    E = 4.5 - 0.25*T;
  else if(T >= 12.0 && T < 16.0)
    E = 2.1- 0.05*T;
  else if(T >= 16.0 && T < 24.0)
    E = 1.5 - 0.0125*T;
  else if(T >= 24.0 && T < 32.0)
    E = 1.35 - 0.00625*T;
  else 
    E = 1.15;
  
  
  //===========================
  //F : The bulk density factor 
  //===========================
  
  F = rhoBulk/ 1600.0;
  
  //==================================
  //Gc : The near size capacity factor 
  //==================================
  Xn = 0.1; //Fraction of near-size feed between 1.25hT and 0.75hT 
  Gc = 0.975*pow((1 - Xn), 0.511);
  
  
  Th = A*B*C*D*E*F*Gc*screenArea;
  
  
  cout <<"A: " << A ;
}
