/*Code snippet only 
  Ref: 
*/

#include <iostream>
#include <math.h>

double sigmaR(){
  return 1.0;
}

double sumEntrapped(double cp, double tf, double tc){
  return 1.0;
}

double sumSolid(double cp, double tf, double tc){
  return 1.0;
}

int main(){
  
  /*
  Variables: 
  Cp_s = Heat capacity of solid phase [kJ/kg.K]
  Cp_e = Heat capacity of entrapped-liquor phase [kJ/kg.K]
  Cp_f = Heat capacity of free-liquor phase [kJ/kg.K]
  
  dH_rxn = Heat of reaction [kJ/kg]
  U = Heat transfer coefficient [kJ/min.K.m3]
  
  D_E = Net energy transported into the chips per volume of diffusing mass
  
  
  */
  
  double Cp_s = 1.47, Cp_e, Cp_f, Cp_e0, Cp_f0, Cp_l, Cp_ext;
  double H_se = 0.0, dH_se, H_f = 0.0, dH_f, dH_rxn = -581.0;
  double M_s, M_s0, M_e, M_e0,  M_f, M_f0, M_ext;
  double m_es, m_el, m_fs, m_fl;
  double V_chips, T_chips, T_chips0, T_f, T_f0, T_ext;
  double U = 827.0, Vcdot, Vbdot, Vfdot_0, Vfdot, Vextdot;
  double epsilon, epsilon0;
  double k, A_T, D_E, D_F;
  double t, deltaT = 0.1;
  
  for(t = 0.0; t < 2000.0; t += deltaT){
   
   //Mixing Rule
    
    Cp_e = Cp_s * m_es + Cp_l * m_el;
    Cp_f = Cp_s * m_fs + Cp_l * m_fl;
    
    D_E = sumEntrapped(Cp_l, T_f, T_chips) + sumSolid(Cp_s, T_f, T_chips);
    
    D_F = -D_E;
    
   
   // dH_se = (Cp_s * M_s + Cp_e * M_e * epsilon) * V_chips * T_chips;
    //Energy balance for wood chips 
    dH_se = Vcdot * ((Cp_s * M_s0 + Cp_e0 * M_e0 * epsilon0) * T_chips0 - (Cp_s * M_s + Cp_e * M_e * epsilon) * T_chips) + (dH_rxn * sigmaR() + U * (T_f - T_chips))* V_chips + Vbdot * (Cp_f * M_f * T_f) + (k * A_T * D_E);
    H_se += dH_se;
    
    //Energy balance for free-liquor
    
    dH_f = Vfdot_0 * (Cp_f0 * M_f0 * T_f0) - Vfdot * (Cp_f * M_f * T_f) + U * V_chips * (T_chips - T_f) - Vbdot * (Cp_f * M_f * T_f) + (k * A_T * D_F) + (Vextdot * Cp_ext * M_ext * T_ext);
    
    H_f += dH_f; 
    
    
    
    
  }
  
  std::cout << dH_se << std::endl;
  
}
