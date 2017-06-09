#ifndef HXER_H
#define HXER_H

#include <pipe.h>


class hxer : public pipe
{
    public:
        double fitRes;
        double heatDuty;
        double Tin, TOut;

        double getflowIn(double p1, double p2, double fitr);
        double getOutletTemp(double dt, double fin, double T, double q);

        hxer();
        virtual ~hxer();

    protected:

    private:
};

#endif // HXER_H
