#ifndef PIPE_H
#define PIPE_H

#include <composition.h>


class pipe : public composition
{
    public:
        double dInner, dOuter;
        double pipeLen;

        double tempIn, tempOut, tempAvg;

        double getflowIn();


        pipe();
        virtual ~pipe();

    protected:

    private:
};

#endif // PIPE_H
