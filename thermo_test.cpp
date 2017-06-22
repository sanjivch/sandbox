#include <iostream>
#include <math.h>
using namespace std;

namespace thermo{
  //public:
    double vp_Antonie(double a, double b, double c, double T){
      return exp(a - b/(T+c));
    }
}

int main(){
  //thermo th1;
  cout << "Hi " << thermo::vp_Antonie(1,2,20,273)<<endl;
  
}
