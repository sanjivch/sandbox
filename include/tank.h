#ifndef TANK_H
#define TANK_H

#include <composition.h>


class tank : public composition
{
    public:
        double diaInner, length, volume;
        double opPressure;
        double heatIn;

        double portInHeight, portOutHeight;//in absolute terms from the bottom of the tank [m]
        double portInHeight2;

        double getVolume(double di, double len);
        double getOpPressure(double inH, double lev);
        double levelAccumulated(double dt, double fin, double fout, double h);
        double enthalpyAccumulated(double dt, double fin1, double fin2, double fout, double tankT, double q, double mass, double enthalpy);
        double massAccumulated(double dt, double fin, double fout, double mass);
        double *calcComposition(double fin1, double fin2, double massInTank, double port1[], double port2[], double tankC[], double num);

        tank();
        virtual ~tank();

    protected:

    private:
};

#endif // TANK_H
