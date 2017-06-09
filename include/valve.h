#ifndef VALVE_H
#define VALVE_H

#include <pipe.h>


class valve : public pipe
{
    public:
        double Cvmax;

        double flowArea();
        double flowVolume();
        double getflowIn(double p1, double p2, double opening);
        valve();
        virtual ~valve();

    protected:

    private:
};

#endif // VALVE_H
