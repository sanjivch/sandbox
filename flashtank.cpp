#include <iostream>
#include <math.h>

using namespace std;
int main(){
  
  
 // Step 1: Determine Inlet Water Properties
double In_Pressure = 869.0; //psig
double Temperature = 500.0;// °F
// from [Steam Property Calculator] => 
double Specific_Enthalpy = 487.8; // btu/lbm; Specific_Enthalpy = hmass_Tp(Temperature,In_Pressure) in SI Units
 
 // Step 2: Determine the Specific Enthalpy and other properties for Saturated Liquid and Gas at Flash Pressure
double Tank_Pressure = 443.8; // psig - Should initialise the tank with some pressure
//[Saturated Properties Calculator] =>
//Saturated Liquid: 
double Specific_Enthalpy_liq = 439.5; // btu/lbm; Specific_Enthalpy_liq = hliq_p(Tank_Pressure)
//Saturated Gas: 
double Specific_Enthalpy_vap = 1205.2;// btu/lbm; Specific_Enthalpy_vap = hvap_p(Tank_Pressure)
 
 // Step 3: Evaluate Flash Tank
/* If Inlet Specific Enthalpy is less than the Saturated Liquid Specific Enthalpy, only liquid leaves the flash tank at inlet specific enthalpy and flash tank pressure.

If Inlet Specific Enthalpy is greater than the Saturated Gas Specific Enthalpy, only Steam leaves the flash tank at inlet specific enthalpy and flash tank pressure.

If Inlet Specific Enthalpy is in between, proceed to Step 4*/

 // Step 4: Determine Flash Properties
 
//Using an mass and energy balance equations:
double MassFlow = 11.1;// = MF

double EnergyFlow = MassFlow * Specific_Enthalpy;

double OutletGasMF, OutletLiquidMF;


for(double t = 0.0; t<100.0; t+=0.1){
  OutletLiquidMF = MassFlow * (Specific_Enthalpy - Specific_Enthalpy_vap) / (Specific_Enthalpy_liq - Specific_Enthalpy_vap); 
//[OutletLiquidMF = 10.4 klb/hr = 11.1 klb/hr * (487.8 btu/lbm - 1,205.2 btu/lbm) / (439.5 btu/lbm - 1,205.2 btu/lbm)]
OutletGasMF = MassFlow - OutletLiquidMF;
//[OutletGasMF = 0.7 klb/hr = 11.1 klb/hr - 10.4 klb/hr]

cout << OutletGasMF<< endl;
}


}
