/*Code snippet only 
  Ref: 
*/
#include <iostream>
#include <math.h>
#define R 0.0083144 //   [kJ/mol. K]

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
  int sComp, CSTR, maxCSTR = 50;
  double eta[50], Area[50], height[50];
  
  double d_rhoS[50][5], rhoS[50][5], rhoS_un[50][5], R_S[50][5], rhoS_sum = 0.0, rhoS_Total = 600.0;
  double e_f[50];
  
  double k1[5], k2[5], A1[5],A2[5], E1[5], E2[5];
  
  double Cp_s = 1.47, Cp_e, Cp_f, Cp_e0, Cp_f0, Cp_l, Cp_ext;
  double H_se = 0.0, dH_se, H_f = 0.0, dH_f, dH_rxn = -581.0;
  double M_s, M_s0, M_e, M_e0,  M_f, M_f0, M_ext;
  double m_es, m_el, m_fs, m_fl;
  double V_chips[50], T_chips, T_chips0, T_f, T_f0, T_ext;
  double U = 827.0, Vcdot, Vbdot, Vfdot_0, Vfdot, Vextdot;
  double epsilon[50];
  double k, A_T, D_E, D_F;
  double T_top;
  double h_factor = 0.0;
  double t, deltaT = 0.1;
  
  std::cin >> T_top;
  for(t = 0.0; t < 2000.0; t += deltaT){
    
    V_chips[CSTR] = (1-eta[CSTR]) * Area[CSTR] * height[CSTR];
    
   
   for(CSTR = 0; CSTR < maxCSTR; ++CSTR){
     
     //Solid-phase components
     for(sComp = 0; sComp < 5; ++sComp){
        
       k1[sComp] = A1[sComp] * exp(-E1[sComp]/ (R * T_chips[CSTR]));
       k2[sComp] = A2[sComp] * exp(-E2[sComp]/ (R * T_chips[CSTR]));
      
       R_S[CSTR][sComp] = -e_f[CSTR] * (k1[sComp] * rhoS[CSTR][0] + k2[sComp] * sqrt(rhoS[CSTR][0] * rhoS[CSTR][2])) * (rhoS[CSTR][sComp] - rhoS_un[CSTR][sComp]);
       
       d_rhoS[CSTR][sComp] = (Vcdot/ V_chips[CSTR]) * (rhoS[CSTR-1][sComp] - rhoS[CSTR][sComp]) + R_S[CSTR][sComp];
       rhoS[CSTR][sComp] += d_rhoS[CSTR][sComp] * deltaT;
       
       rhoS_sum += rhoS[CSTR][sComp];
     }
     
     //Porosity Calculation
     epsilon[CSTR] = 1 - rhoS_sum/ rhoS_Total;
     //Change in porosity 
     
     
     //Entrapped-liquor-phase components
     
   }
   
   
   
   //Mixing Rule
    
    Cp_e = Cp_s * m_es + Cp_l * m_el;
    Cp_f = Cp_s * m_fs + Cp_l * m_fl;
    
    D_E = sumEntrapped(Cp_l, T_f, T_chips) + sumSolid(Cp_s, T_f, T_chips);
    
    D_F = -D_E;
    
   
   // dH_se = (Cp_s * M_s + Cp_e * M_e * epsilon[CSTR) * V_chips[CSTR * T_chips;
    //Energy balance for wood chips 
    dH_se = Vcdot * ((Cp_s * M_s0 + Cp_e0 * M_e0 * epsilon[CSTR-1]) * T_chips0 - (Cp_s * M_s + Cp_e * M_e * epsilon[CSTR]) * T_chips) + (dH_rxn * sigmaR() + U * (T_f - T_chips))* V_chips[CSTR] + Vbdot * (Cp_f * M_f * T_f) + (k * A_T * D_E);
    H_se += dH_se;
    
    //Energy balance for free-liquor
    
    dH_f = Vfdot_0 * (Cp_f0 * M_f0 * T_f0) - Vfdot * (Cp_f * M_f * T_f) + U * V_chips[CSTR] * (T_chips - T_f) - Vbdot * (Cp_f * M_f * T_f) + (k * A_T * D_F) + (Vextdot * Cp_ext * M_ext * T_ext);
    
    H_f += dH_f; 
    
    
    h_factor += exp(43.2 - 16115/T_top)*deltaT;
    
  }
  
  std::cout << dH_se << " " << h_factor << std::endl;
  return 0;
}
