#ifndef CHASSIS_H_
#define CHASSIS_H_
#include <math.h>

class drivetrain
{
    private:
        double wheelvolt[4] = {0};

        vex::brakeType stopBrakeType;

        void setMotorVolt();
    public:
        drivetrain();
        void setStopBrakeType(brakeType brake);
        void chassisBrake(brakeType brake);
        void chassisRun();
};

#endif