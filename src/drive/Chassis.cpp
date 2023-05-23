#include "vex.h"
//#include "drivetrain.h"
#include <cmath>
#include <iostream>
using namespace vex;
using namespace std;


Chassis::Chassis(){
    stopBrakeType = coast;
}

void Chassis::setDriveVolt(double motorVolt[]){
    for (int i = 0; i < 4; i++)
    {
        driveVolt[i] = motorVolt[i];
    }
}
void Chassis::setMotorVolt(){
    if (driveVolt[0] == 0)
    {
        rightFront.stop(stopBrakeType);
    }
    else
    {
        rightFront.spin(directionType::fwd, driveVolt[0], voltageUnits::volt);
    }

    if (driveVolt[1] == 0)
    {
        leftFront.stop(stopBrakeType);
    }
    else
    {
        leftFront.spin(directionType::fwd, driveVolt[1], voltageUnits::volt);
    }

    // if (driveVolt[2] == 0)
    // {
    //     rightBack.stop(stopBrakeType);
    // }
    // else
    // {
    //     rightBack.spin(directionType::fwd, driveVolt[2], voltageUnits::volt);
    // }

    // if (driveVolt[3] == 0)
    // {
    //     leftBack.stop(stopBrakeType);
    // }
    // else
    // {
    //     leftBack.spin(directionType::fwd, driveVolt[3], voltageUnits::volt);
    // }
}
void Chassis::chassisRun()
{ 
    setMotorVolt();
}
void Chassis::setStopBrakeType(brakeType brake){
    stopBrakeType = brake;
}

void Chassis::chassisHold(brakeType hold){
    for (int i = 0; i < 4; i++)
    {
        driveVolt[i] = 0;
    }
    rightFront.stop(hold);
    leftFront.stop(hold);
    rightBack.stop(hold);
    leftBack.stop(hold);
}



void updateChassis()
{
    while(true)
    {
        Chassis::getInstance()->chassisRun();
        this_thread::sleep_for(10);
    }   
}

/*
#ifndef CHASSIS_H_
#define CHASSIS_H_
#include <math.h>

class Chassis
{
    private:
        double driveVolt[4] = {0};

        vex::brakeType stopBrakeType;
        void calcdriveVolt();
        void setMotorVolt();
    public:
        Chassis();
        void setStopBrakeType(brakeType brake);
        void chassisBrake(brakeType brake);
        void chassisRun();
};

#endif

*/