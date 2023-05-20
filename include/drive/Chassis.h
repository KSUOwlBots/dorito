#ifndef CHASSIS_H_
#define CHASSIS_H_
#include <math.h>

class Chassis
{
    private:
        double driveVolt[4] = {0};

        vex::brakeType stopBrakeType;
        void setMotorVolt();
    public:
        static Chassis *getInstance(){
            static Chassis *c = NULL;
            if (c == NULL){
                c = new Chassis();
            }
            return c;
        }
        static void deleteInstance(){
            Chassis *c = Chassis::getInstance();
            if(c != NULL){
                delete c;
                c = NULL;
            }
        }
        Chassis();
        void setDriveVolt(double motorVolt[]);
        void setStopBrakeType(brakeType brake);
        void chassisHold(brakeType hold);
        void chassisRun();
};

void updateChassis();

#endif