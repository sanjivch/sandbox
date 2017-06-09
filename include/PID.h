#ifndef PID_H
#define PID_H


class PID
{
    public:

        double PV, SP, CO;
        double error, Kc, Ti, Td;
        double deadband, ramptime;

        double controlPID(double dt, double pv, double sp, double Kc, double Ti, double integral);
        double errorIntegral(double dt, double pv, double sp, double iError);

        PID();
        virtual ~PID();

    protected:

    private:
};

#endif // PID_H
