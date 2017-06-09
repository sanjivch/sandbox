#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <composition.h>


class boundary : public composition
{
    public:
        double pressureIn;
        double temperatureIn;
        double pressureOut;



        boundary();
        virtual ~boundary();

    protected:

    private:
};

#endif // BOUNDARY_H
