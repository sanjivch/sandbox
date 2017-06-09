#ifndef PUMP_H
#define PUMP_H

#include <pipe.h>


class pump : public pipe
{
    public:

        int runFlag; //0 = Stop; 1= Run
        double a0, a1, a2; //Pump curve coefficients
        double speed;


        double getflowIn(double p1, double p2, double a, double b, double c, double ns, int flag);
        double getPowerConsumed();

        pump();
        virtual ~pump();

    protected:

    private:
};

#endif // PUMP_H
