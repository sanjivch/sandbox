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
#define N 50
#define O 6
#define P 5

template<class Init2D>
void init2Da(Init2D A[N][O])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<O; j++){
           A[i][j] = 0.0;
           //std::cout <<i << " "<< A[i][j] << " " ;
        }
        //std::cout << "\n";
    }
}

template<class Init2D>
void init2Db(Init2D A[N][P])
{
  for (int i=0; i<N; i++)
    {
        for (int j=0; j<P; j++){
           A[i][j] = 0.0;
           //std::cout <<i << " "<< A[i][j] << " " ;
        }
       // std::cout << "\n";
    }
}

template<class Init1D>
void init1D(Init1D A[N])
{
    for (int i=0; i<N; i++)
    {
       A[i] = 0.0;
       //std::cout << i << " " << A[i] << " " << std::endl;

    }
}

template<class Init1D>
void Init1DT(Init1D A[N])
{
  for (int i=0; i<N; i++)
    {
       A[i] = 273.15;
       //std::cout << i << " " << A[i] << " " << std::endl;

    }
}

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


    VARIABLES:

    V_freef = Volume of free liquor [m3]
    V = Volume of CSTR [m3]
    V_chips = Volume of chip [m3]
    Vs = Volume of solid [m3]
    V_entrap = Volume of entrapped liquor [m3]

    eta = Volume fraction of the free liquor and the wood chips
    epsilon = volume fraction of the wood chip that is occupied by the entrapped liquor (porosity)

    Area = Cross-sectional area of the CSTR corresponding to digester [m2]

    Solid-phase components:

    s1 = High-reactive lignin
    s2 = Low-reactive lignin
    s3 = Cellulose
    s4 = Araboxylan
    s5 = Galactoglucomman

    Entrapped-liquor-phase components:

    e1 = active effective alkali
    e2 = passive effective alkali
    e3 = active hydrosulfide
    e4 = passive hydrosulfide
    e5 = dissolved lignin
    e6 = dissolved carbohydrates

    Free-liquor-phase components:

    f1 = active effective alkali
    f2 = passive effective alkali
    f3 = active hydrosulfide
    f4 = passive hydrosulfide
    f5 = dissolved lignin
    f6 = dissolved carbohydrates


    A1[i], A2[i] = pre-exponential factors for component, i [m3/ kg.min]
    E1[i], E2[i] = activation energies for component, i [kJ/ mol.K]
    k1[i], k2[i] = kinectic rate constants for component, i [m3/ kg.min]

    mS[i] = mass fraction of solid component, i [kg/kg]
    mS_in[i] = mass fraction of solid component, i, entering [kg/kg]
    mS_ur[i] = mass fraction of solid component, i, unreacted [kg/kg]
    mE[i] = mass fraction of entrapped-liquor component, i [kg/kg]
    mF[i] = mass fraction of free-liquor component, i [kg/kg]

    rhoS = density of solid material [kg/m3]
    rhoS[i] = density of solid component, i [kg/m3]

    rhoE =  density of entrapped-liquor [kg/m3]
    rhoE[i] = density of entrapped-liquor component, i [kg/m3]

    rhoF = density of free-liquor [kg/m3]
    rhoF[i] = density of free-liquor component, i [kg/m3]

    Cp_S = Heat capacity of solid phase [kJ/kg.K]
    Cp_E = Heat capacity of entrapped-liquor phase [kJ/kg.K]
    Cp_F = Heat capacity of free-liquor phase [kJ/kg.K]
    Vc_dot = Volumetric flow rate of chips [m3/s]

    kappa = measure of residual lignin in wood chips
    yield = measure of amount of wood substance recovered to amount of wood substance fed

 */
 
  int sComp, eComp, fComp, CSTR, maxCSTR = 50;
  
  double eta[50];
  static double Area[] = {17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,17.9854,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,18.6793,19.865,19.865,19.865,21.0871,21.0871,21.0871,21.0871};
  static double height[] = {0.623,0.623,0.623,0.623,0.623,0.5944,0.5944,0.5944,0.5944,0.4775,0.4775,0.4775,0.6096,0.6096,0.6096,0.5182,0.5182,0.5182,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.701,0.4877,0.4877,0.4877,0.6477,0.6477,0.6477,0.6477,0.6477,0.6477,0.6477,0.6477,0.3962,0.7925,0.3962,1.1278,0.6096,1.0058,1.0058};

  double d_rhoS[50][5], rhoS[50][5], rhoS_un[50][5], R_S[50][5], sumR_S[50], rhoS_Total = 600.0, rho_water = 997.03;
  double rhoS_sum[50], d_rhoS_sum[50];

  double d_rhoE[50][6], rhoE[50][6], R_E[50][6];
  double rhoEL_sum[50], rhoES_sum[50];
  double d_rhoF[50][6], rhoF[50][6], rhoF_sum = 0.0;
  double rhoFL_sum[50], rhoFS_sum[50], rhoF_ext[50];

  double dT_free[50], dT_chips[50];

  double e_f[50], D[50];

  double k1[5], k2[5];
  static double A1[] = {0.3954, 1.457E+11, 28.09, 7.075, 5826.7 };
  static double A2[] = {12.49, 1.873, 124.9, 47.86, 3.225E+16 };
  static double E1[] = {29.3, 115.0, 34.7, 25.1, 73.3};
  static double E2[] = {31.4, 37.7, 41.9, 37.7, 167.0};
  
  double b[6][5];

  double Cp_s = 1.47, Cp_e[50], Cp_f[50], Cp_e0, Cp_f0, Cp_l, Cp_ext, Cp_x, Cp_fext[50];
  double H_se = 0.0, dH_se, H_f = 0.0, dH_f, dH_rxn = -581.0;
  double M_s[50], M_s0, M_e[50], M_e0,  M_f[50], M_f0, M_ext, M_sdot[50], M_edot[50], M_fext[50];
  double M_es[50], M_el[50], M_fs[50], M_fl[50], M_fdot[50];
  double V_chips[50], V_entrap[50], V_free[50];
  double T_chips[50], T_free[50], T_f0, T_ext;
  double U = 827.0, Vcdot, Vbdot[50], Vfdot_0, Vfdot[50], Vfdot_in[50], Vfdot_out[50], Vextdot[50];
  double epsilon[50], d_epsilon[50];
  double betaOHL, betaHSL, betaOHC;
  double k, A_T, D_sum[50], D_E[50], D_F[50];
  double T_top, T_x;
  double h_factor = 0.0;
  double t, deltaT = 0.1;

  //Initialize all the arrays

  init1D(rhoS_sum);
  init1D(d_rhoS_sum);
  init1D(rhoEL_sum);
  init1D(rhoES_sum);
  init1D(rhoFL_sum);
  init1D(rhoFS_sum);
  init1D(rhoF_ext);
  init1D(dT_free);
  init1D(dT_chips);
  init1D(e_f);
  init1D(M_sdot);
  init1D(M_edot);
  init1D(eta);
  
  Init1DT(T_chips);
  
  init2Db(d_rhoS);
  init2Db(rhoS);
  init2Db(rhoS_un);
  init2Db(R_S);
  
  //double d_rhoS[50][5], rhoS[50][5], rhoS_un[50][5], R_S[50][5],
  init2Da(d_rhoE);
  init2Da(rhoE);
  init2Da(R_E);
  init2Da(d_rhoF);
  init2Da(rhoF);
  //double d_rhoE[50][6], rhoE[50][6], R_E[50][6];


  
  for(t = 0.0; t < 2.0; t += deltaT){


   for(CSTR = 0; CSTR < maxCSTR; CSTR++){
      
      V_chips[CSTR] = (1-eta[CSTR]) * Area[CSTR] * height[CSTR];
      //std::cout << V_chips[CSTR] << " " << eta[CSTR] << std::endl;
      
     //Solid-phase components
     for(sComp = 0; sComp < 5; sComp++){

       k1[sComp] = A1[sComp] * exp(-E1[sComp]/ (R * T_chips[CSTR]));
       k2[sComp] = A2[sComp] * exp(-E2[sComp]/ (R * T_chips[CSTR]));
       
       std::cout << k1[sComp] << " " << k2[sComp] << std::endl;

       R_S[CSTR][sComp] = -e_f[CSTR] * (k1[sComp] * rhoS[CSTR][0] + k2[sComp] * sqrt(rhoS[CSTR][0] * rhoS[CSTR][2])) * (rhoS[CSTR][sComp] - rhoS_un[CSTR][sComp]);

       d_rhoS[CSTR][sComp] = ((Vcdot/ V_chips[CSTR]) * (rhoS[CSTR-1][sComp] - rhoS[CSTR][sComp]) + R_S[CSTR][sComp]) * deltaT;
       rhoS[CSTR][sComp] += d_rhoS[CSTR][sComp] * deltaT;

       d_rhoS_sum[CSTR] += d_rhoS[CSTR][sComp];
       rhoS_sum[CSTR] += rhoS[CSTR][sComp];

       sumR_S[CSTR] += R_S[CSTR][sComp];
    }

     //Porosity Calculation
     epsilon[CSTR] = 1 - rhoS_sum[CSTR]/ rhoS_Total;

     //Change in porosity
     d_epsilon[CSTR] = -d_rhoS_sum[CSTR]/ rhoS_Total;

     V_entrap[CSTR] = epsilon[CSTR] * (1 - eta[CSTR]) * Area[CSTR] * height[CSTR];

     //Entrapped-liquor-phase components
     for(eComp = 0; eComp < 6; eComp++){
       
	   fComp = eComp;



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
       
	   //R_E[CSTR][eComp] =
       D[CSTR] = 6.1321 * sqrt(T_chips[CSTR]) * exp(-4870.0/(1.98 * T_chips[CSTR]));

       Vbdot[CSTR] = -sumR_S[CSTR]/ rhoS_Total;

       d_rhoE[CSTR][eComp] = ((-rhoE[CSTR][eComp] * d_epsilon[CSTR]/ epsilon[CSTR]) + Vcdot * (rhoE[CSTR-1][eComp] * epsilon[CSTR-1] - rhoE[CSTR][eComp] * epsilon[CSTR])/ V_entrap[CSTR] + D[CSTR] * (rhoF[CSTR][fComp] - rhoE[CSTR][eComp]) + (R_E[CSTR][eComp]/ epsilon[CSTR]) + (Vbdot[CSTR] * rhoF[CSTR][fComp])/V_entrap[CSTR]) * deltaT;

       rhoE[CSTR][eComp] += d_rhoE[CSTR][eComp];

      if(eComp < 5)
        rhoEL_sum[CSTR] += rhoE[CSTR][eComp];
      else
        rhoES_sum[CSTR] += rhoE[CSTR][eComp];
    }

     V_free[CSTR] = eta[CSTR] * Area[CSTR] * height[CSTR];
     //free-liquor-phase components
     for(fComp = 0; fComp < 6; fComp++){

       //External flows into the digester
       Vfdot_in[CSTR] = Vfdot_out[CSTR -1];
       Vfdot_out[CSTR] = Vfdot_in[CSTR] - Vbdot[CSTR] + Vextdot[CSTR];


       d_rhoF[CSTR][fComp] = ((Vfdot_in[CSTR] * rhoF[CSTR-1][fComp] - Vfdot_out[CSTR] * rhoF[CSTR][fComp])/V_free[CSTR] + (D[CSTR] * epsilon[CSTR] * (1 - eta[CSTR]) * (rhoE[CSTR][fComp] - rhoF[CSTR][fComp])/ eta[CSTR]) + (Vbdot[CSTR] * rhoF[CSTR][fComp] + Vextdot[CSTR] * rhoF_ext[CSTR])/ V_free[CSTR]) * deltaT;
       rhoF[CSTR][fComp] += d_rhoF[CSTR][fComp];

       if(fComp < 5)
        Cp_x = Cp_l;
       else
        Cp_x = Cp_s;

       if(rhoF[CSTR][fComp] > rhoE[CSTR][fComp])
        T_x = T_free[CSTR];
       else
        T_x = T_chips[CSTR];


       D_sum[CSTR] += (rhoF[CSTR][fComp] - rhoE[CSTR][fComp]) * Cp_x * T_x ;


     }


     M_s[CSTR] = rhoS_sum[CSTR];

     M_el[CSTR] = rhoEL_sum[CSTR] + rho_water;
     M_es[CSTR] = rhoES_sum[CSTR];

     M_fl[CSTR] = rhoFL_sum[CSTR] + rho_water;
     M_fs[CSTR] = rhoFS_sum[CSTR];

     M_e[CSTR] = M_el[CSTR] + M_es[CSTR];
     M_f[CSTR] = M_fl[CSTR] + M_fs[CSTR];


     //Mixing Rule

     Cp_e[CSTR] = Cp_s * M_es[CSTR]/ M_e[CSTR] + Cp_l * M_el[CSTR]/M_e[CSTR];
     Cp_f[CSTR] = Cp_s * M_fs[CSTR]/ M_f[CSTR] + Cp_l * M_fl[CSTR]/M_f[CSTR];



     D_E[CSTR] = D_sum[CSTR];

     D_F[CSTR] = -D_sum[CSTR];


    //Wood chips temperature

     dT_chips[CSTR] = ((Cp_s * M_sdot[CSTR] + Cp_e[CSTR] * M_e[CSTR] * d_epsilon[CSTR] + Cp_e[CSTR] * M_edot[CSTR] * epsilon[CSTR]) * T_chips[CSTR]/ (Cp_s * M_s[CSTR] + Cp_e[CSTR] * M_e[CSTR] * epsilon[CSTR]) + Vcdot * (Cp_s * M_s[CSTR-1] + Cp_e[CSTR-1] * M_e[CSTR-1] * epsilon[CSTR-1]) * (T_chips[CSTR-1] - T_chips[CSTR])/ (V_chips[CSTR] * (Cp_s * M_s[CSTR] + Cp_e[CSTR] * M_e[CSTR] * epsilon[CSTR])) + dH_rxn * sumR_S[CSTR]/ (Cp_s * M_s[CSTR] + Cp_e[CSTR] * M_e[CSTR] * epsilon[CSTR]) + U * (T_free[CSTR] - T_chips[CSTR])/ (Cp_s * M_s[CSTR] + Cp_e[CSTR] * M_e[CSTR] * epsilon[CSTR]) + Vbdot[CSTR] * (Cp_f[CSTR] * M_f[CSTR] * T_free[CSTR])/ (V_chips[CSTR] * (Cp_s * M_s[CSTR] + Cp_e[CSTR] * M_e[CSTR] * epsilon[CSTR])) + D[CSTR] * D_E[CSTR]/ (Cp_s * M_s[CSTR] + Cp_e[CSTR] * M_e[CSTR] * epsilon[CSTR])) * deltaT;
     T_chips[CSTR] += dT_chips[CSTR];

     //Free-liquor temperature
	 
     dT_free[CSTR] = ((M_fdot[CSTR] * T_free[CSTR]) * M_f[CSTR] + (Vfdot[CSTR+1] * Cp_f[CSTR+1] * M_f[CSTR+1]) * T_free[CSTR+1]/ (V_free[CSTR] * Cp_f[CSTR] * M_f[CSTR]) - (Vfdot[CSTR]/ V_free[CSTR]) * T_free[CSTR] + U * (T_chips[CSTR] - T_free[CSTR]) * (1 - eta[CSTR])/ (Cp_f[CSTR] * M_f[CSTR] * eta[CSTR]) - Vbdot[CSTR] * T_free[CSTR]/ V_free[CSTR] + (D[CSTR] * D_F[CSTR] * (1 - eta[CSTR]))/ (Cp_f[CSTR] * M_f[CSTR] * eta[CSTR]) + (Cp_fext[CSTR] * M_fext[CSTR] * Vextdot[CSTR]) * T_ext/ (Cp_f[CSTR] * M_f[CSTR] * V_free[CSTR])) * deltaT;
     T_free[CSTR] += dT_free[CSTR];
  }
 
 
  eta[CSTR] = V_free[CSTR]/ (Area[CSTR] * height[CSTR]);
  
  std::cout << "End of cycle \n" ; 

  }

  
  return 0;
}


  /*  for(int i = 0; i < 5; ++i){
        std::cin >> rhoS[i];
    }

    kappa = (rhoS[0] + rhoS[1])/(0.00153* (rhoS[0] + rhoS[1] + rhoS[2] + rhoS[3] + rhoS[4]));

    yield = 600.0/ (rhoS[0] + + rhoS[1] + rhoS[2] + rhoS[3] + rhoS[4]);

    std::cout << A1[0] << " " << kappa << " " << yield << std::endl;

*/

