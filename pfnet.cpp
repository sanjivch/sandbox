#include <iostream>
#include <math.h>
using namespace std;

int main(){
 double p1=1013.25, p2 = 101.325, p3 = 101.325, p4 = 900, p5=500;
 double m12, m23, m34, m45;
 double f12 = 0.25, f23 = 0.21, f34 = 0.27, f45 = 1.98;
 int i;
 
 for(i =1; i < 3000; i++){
   m12 = f12*sqrt(abs(p1-p2));
   m23 = f23*sqrt(abs(p2-p3));
   m34 = f34*sqrt(abs(p3-p4));
  // m45 = f45*sqrt(abs(p4-p5));
   
   if(m12!=m23){
     p2 = p2 + 1*(m12-m23);
     if(m23!= m34){
       p3 = p3 - 1*(m23-m34);
     }
   }
  /* if(m12!=m23){
     p2 = p2 + 1*(m12-m23);
     if(m23!= m34){
       p3 = p3 - 1*(m23-m34);
       if(m34!= m45){
         p4 = p4 - 1*(m34-m45);
       }
     }
   }*/
    
   
   cout << m12 << " " << p2 << " "<< m23 << " " << p3 << " " << m34 <<  endl;
   if(abs(m12- m23) < 0.01 && abs(m23- m34) < 0.01 )
    break;
   
 }
 cout << i << endl;
}
