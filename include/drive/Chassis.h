#ifndef CHASSIS_H_
#define CHASSIS_H_
#include <math.h>

class Chassis
{
    private:
        double driveVolt[4] = {0,0,0,0};
        vex::brakeType stopBrakeType;
        float leftTrackerCenterDistance;
        float leftTrackerDiameter;
        float leftTrackerInToDegRatio;
        float rightTrackerCenterDistance;
        float rightTrackerDiameter;
        float rightTrackerInToDegRatio;
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
        Chassis(float leftTrackerDiameter, float leftTrackerCenterDistance, float rightTrackerDiameter, float rightTrackerCenterDistacne);
        Chassis();
        float get_absolute_heading();
        odom odom;
        float getLeftTrackerPos();
        float getRightTrackerPos();
        void set_coordinates(float X_position, float Y_position, float orientation_deg);
        void position_track();
        static int position_track_task();
        vex::task odom_task;
        float getXPos();
        float getYPos();
        void drivetoPoint(float X_position, float Y_position);
        void driveToPoint(float X_position, float Y_position, float angle);
        void driveToPoint(float X_position, float Y_position, float angle, float drive_max_voltage, float heading_max_voltage);
        void driveToPoint(float X_position, float Y_position, float angle, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout);
        void driveToPoint(float X_position, float Y_position, float angle, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);


        void setDriveVolt(double motorVolt[]);
        void setStopBrakeType(brakeType coast);
        void chassisHold(brakeType hold);
        void chassisRun();
        };

void updateChassis();
#endif