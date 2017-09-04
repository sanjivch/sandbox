/*
Continuous Digester Model 
Author: Sanjiv Chemudupati
Ref:  Fundamental continuous-pulp-digester model for simulation and control
      Philip A Wisnewski; Francis J Doyle III; Ferhan Kayihan
      American Institute of Chemical Engineers. AIChE Journal; Dec 1997; 43, 12; Research Library
      pg. 3175
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
  int sComp, eComp, fComp, CSTR, maxCSTR = 50;
  double eta[50], Area[50], height[50];
  
  double d_rhoS[50][5], rhoS[50][5], rhoS_un[50][5], R_S[50][5], sumR_S[50], rhoS_sum = 0.0, d_rhoS_sum = 0.0, rhoS_Total = 600.0;
  
  double d_rhoE[50][6], rhoE[50][6], R_E[50][6], rhoE_sum = 0.0;
  
  double d_rhoF[50][6], rhoF[50][6], rhoF_sum = 0.0;
  
  double e_f[50], D[50];
  
  double k1[5], k2[5];
  static double A1[] = {0.3954, 1.457E+11, 28.09, 7.075, 5826.7 };
  static double A2[] = {12.49, 1.873, 124.9, 47.86, 3.225E+16 };
  static double E1[] = {29.3, 115.0, 34.7, 25.1, 73.3};
  static double E2[] = {31.4, 37.7, 41.9, 37.7, 167.0};
  
  double Cp_s = 1.47, Cp_e, Cp_f, Cp_e0, Cp_f0, Cp_l, Cp_ext;
  double H_se = 0.0, dH_se, H_f = 0.0, dH_f, dH_rxn = -581.0;
  double M_s, M_s0, M_e, M_e0,  M_f, M_f0, M_ext;
  double m_es, m_el, m_fs, m_fl;
  double V_chips[50], V_entrap[50]; 
  double T_chips[50], T_f, T_f0, T_ext;
  double U = 827.0, Vcdot, Vbdot[50], Vfdot_0, Vfdot, Vextdot;
  double epsilon[50], d_epsilon[50];
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
       
       d_rhoS_sum += d_rhoS[CSTR][sComp];
       rhoS_sum += rhoS[CSTR][sComp];
       
       sumR_S[CSTR] += R_S[CSTR][sComp];
    }
     
     //Porosity Calculation
     epsilon[CSTR] = 1 - rhoS_sum/ rhoS_Total;
    
     //Change in porosity 
     d_epsilon[CSTR] = -d_rhoS_sum/ rhoS_Total;
     
     V_entrap[CSTR] = epsilon[CSTR] * (1 - eta[CSTR]) * Area[CSTR] * height[CSTR];
     //Entrapped-liquor-phase components
     for(eComp = 0; eComp < 6; ++eComp){
       fComp = eComp;
       
       /*
       double b[6][5];
    
    double betaOHL, betaHSL, betaOHC;
    
    betaOHC = 0.5;
    betaHSL = 0.25;
    betaOHL = 0.75;
    
    
    b[0][0] = betaOHL - 0.5 * betaHSL;
    b[0][1] = betaOHL - 0.5 * betaHSL;
    b[0][2] = betaOHC;
    b[0][3] = betaOHC;
    b[0][4] = betaOHC;
    
    
    b[1][0] = -b[0][0];
    b[1][1] = -b[0][1];
    b[1][2] = -b[0][2];
    b[1][3] = -b[0][3];
    b[1][4] = -b[0][4];
    
    
    b[2][0] = 0.5 * betaHSL;
    b[2][1] = 0.5 * betaHSL;
    b[2][2] = 0.0;
    b[2][3] = 0.0;
    b[2][4] = 0.0;
    
    
    b[3][0] = -b[2][0];
    b[3][1] = -b[2][1];
    b[3][2] = -b[2][2];
    b[3][3] = -b[2][3];
    b[3][4] = -b[2][4];
    
    
    b[4][0] = -1.0;
    b[4][1] = -1.0;
    b[4][2] = 0.0;
    b[4][3] = 0.0;
    b[4][4] = 0.0;
    
    b[5][0] = -1.0 - b[4][0];
    b[5][1] = -1.0 - b[4][1];
    b[5][2] = -1.0 - b[4][2];
    b[5][3] = -1.0 - b[4][3];
    b[5][4] = -1.0 - b[4][4];
       
       */
       
           
       //R_E[CSTR][eComp] = 
       D[CSTR] = 6.1321 * sqrt(T_chips[CSTR]) * exp(-4870.0/(1.98 * T_chips[CSTR]));
       
       Vbdot[CSTR] = -sumR_S[CSTR]/ rhoS_Total;
       
       d_rhoE[CSTR][eComp] = (-rhoE[CSTR][eComp] * d_epsilon[CSTR]/ epsilon[CSTR]) + Vcdot * (rhoE[CSTR-1][eComp] * epsilon[CSTR-1] - rhoE[CSTR][eComp] * epsilon[CSTR])/ V_entrap[CSTR] + D[CSTR] * (rhoF[CSTR][fComp] - rhoE[CSTR][eComp]) + (R_E[CSTR][eComp]/ epsilon[CSTR]) + (Vbdot[CSTR] * rhoF[CSTR][fComp])/V_entrap[CSTR];
    }
     
     V_free = eta[CSTR] * Area[CSTR] * height[CSTR];
     //free-liquor-phase components
     for(fComp = 0; fComp < 6; ++fComp){
       
       Vfdot_in[CSTR] = Vfdot_out[CSTR -1];
       Vfdot_out[CSTR] = Vfdot_in[CSTR] - Vbdot[CSTR] + Vextdot;
       
       
       d_rhoF[CSTR][fComp] = (Vfdot_in[CSTR] * rhoF[CSTR-1][fComp])/V_free[CSTR] - (Vfdot_out[CSTR] * rhoF[CSTR][fComp])/V_free + (D[CSTR] * epsilon[CSTR] * (1 - eta[CSTR]) * (rhoE[CSTR][fComp] - rhoF[CSTR][fComp])/ eta[CSTR]) + (Vbdot[CSTR] * rhoF[CSTR][fComp] + Vextdot * rhoF_ext[fComp])/ V_free[CSTR] ;
     }
     
     
  }
   
   
   
   //Mixing Rule
    
    Cp_e = Cp_s * m_es + Cp_l * m_el;
    Cp_f = Cp_s * m_fs + Cp_l * m_fl;
    
    D_E = sumEntrapped(Cp_l, T_f, T_chips[CSTR]) + sumSolid(Cp_s, T_f, T_chips[CSTR]);
    
    D_F = -D_E;
    
   
   // dH_se = (Cp_s * M_s + Cp_e * M_e * epsilon[CSTR) * V_chips[CSTR * T_chips;
    //Energy balance for wood chips 
    dH_se = Vcdot * ((Cp_s * M_s0 + Cp_e0 * M_e0 * epsilon[CSTR-1]) * T_chips[CSTR-1] - (Cp_s * M_s + Cp_e * M_e * epsilon[CSTR]) * T_chips[CSTR]) + (dH_rxn * sigmaR() + U * (T_f - T_chips[CSTR]))* V_chips[CSTR] + Vbdot[CSTR] * (Cp_f * M_f * T_f) + (k * A_T * D_E);
    H_se += dH_se;
    
    //Energy balance for free-liquor
    
    dH_f = Vfdot_0 * (Cp_f0 * M_f0 * T_f0) - Vfdot * (Cp_f * M_f * T_f) + U * V_chips[CSTR] * (T_chips[CSTR] - T_f) - Vbdot[CSTR] * (Cp_f * M_f * T_f) + (k * A_T * D_F) + (Vextdot * Cp_ext * M_ext * T_ext);
    
    H_f += dH_f; 
    
    
    h_factor += exp(43.2 - 16115/T_top)*deltaT;
    
  }
  
  std::cout << dH_se << " " << h_factor << std::endl;
  return 0;
}
