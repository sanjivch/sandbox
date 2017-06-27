#include <iostream>
#include <math.h>
using namespace std;

namespace thermo{
  //public:
    double a(double, double);//declare the function before!!
    double vp_Antonie(double a, double b, double c, double T){
      return exp(a - b/(T+c));
    }
    
    double SRK_P(double T, double P, double omega, double V){
      //return 0;
      a(T,P);
    }
    
    double a(double T, double P){
      return 0.42747*pow(8.314*T,2)/P;
    }
    
    double nr(){
      double xn = 1.5, xn1;
      double tolerance = 0.001;
      for(int i =1; i < 10; i++){
        xn1 =xn - (pow(xn,3)+(4*pow(xn,2))-10)/(3*pow(xn,2)+ 8*xn);
        cout << xn << endl;
        if(abs(xn1 - xn) < tolerance)
          break;
        
        xn = xn1;
      }
      return xn;
    }
    
    double nr_srk(double R, double T, double P,double alpha, double a, double b){
      double vn, vn1;
      vn = R*T/P;//Initial guess from ideal gas law
      double tolerance = 0.001;
      
      double f_v, df_v;
      
      
      for(int i =1; i < 10; i++){
        
        f_v = P - (R*T/(vn - b)) + (alpha*a/(vn*(vn+b)));
        df_v = (R*T/pow(vn - b,2)) + (alpha*a*(2*vn + b)/pow(vn*(vn+b),2));
        
        vn1 =vn - f_v/df_v;
        
        cout << vn << endl;
        if(abs(vn1 - vn) < tolerance)
          break;
        
        vn = vn1;
      }
      return vn;
    }
}
/*A gas cylinder with a volume of 2.50 m3 contains 1.00 kmol of carbon dioxide at T = 300 K.Use the SRK equation of state to estimate the gas pressure in atm. Data for carbon dioxide:
  Tc = 304.2 K, pc = 72.9 atm, and ω = 0.225
*/
    

int main(){
  //thermo th1;
  cout << thermo::vp_Antonie(1,2,20,273)<<endl;
  cout << thermo::SRK_P(304.2, 72.9, 0.225, 2.5) << endl;
  //cout << thermo::nr()<<endl;
  cout << thermo::nr_srk(8.314, 423, 70, 1,1,1)<< endl;
  
  
}
