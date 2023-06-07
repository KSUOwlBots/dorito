#include "vex.h"
//#include "drivetrain.h"
#include <cmath>
#include <iostream>
using namespace vex;
using namespace std;


Chassis::Chassis(float leftTrackerDiameter, float leftTrackerCenterDistance, float rightTrackerDiameter, float rightTrackerCenterDistacne) :
    leftTrackerCenterDistance(leftTrackerCenterDistance),
    leftTrackerDiameter(leftTrackerDiameter),
    leftTrackerInToDegRatio(leftTrackerDiameter * M_PI / 360),
    rightTrackerCenterDistance(rightTrackerCenterDistacne),
    rightTrackerDiameter(rightTrackerDiameter),
    rightTrackerInToDegRatio(rightTrackerDiameter * M_PI / 360),
    {
        odom.set_physical_distances(leftTracckerCenterDistance, rightTrackerCenterDistance);
        odom_task = task(position_track_task);
        set_coordinates(0,0,0);
    }
/*
Chassis(float leftTrackerDiameter, float leftTrackerCenterDistance, float rightTrackerDiameter, float rightTrackerCenterDistacne);
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
        void setStopBrakeType(brakeType brake);
        void chassisHold(brakeType hold);
        void chassisRun();
        };

*/
float Chassis::get_absolute_heading(){ 
  return( reduce_0_to_360( Gyro.rotation()*360.0/gyro_scale ) ); 
}
float Chassis::getLeftTrackerPos(){
    return (leftTrackerPosition.position(deg)*leftTrackerInToDegRatio);
}
float Chassis::getRightTrackerPos(){
    return (rightTrackerPosition.position(deg)*rightTrackerInToDegRatio);
}
void Chassis::position_track(){
    odom.update_position(getLeftTrackerPos(), getRightTrackerPos(), odom.orientation_deg);
}
void Chassis::set_coordinates(float X_position, float Y_position, float orientation_deg){
    odom.set_coordinates(X_position, Y_position, orientation_deg, getLeftTrackerPos(), getRightTrackerPos());
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

    if (driveVolt[2] == 0)
    {
        rightBack.stop(stopBrakeType);
    }
    else
    {
        rightBack.spin(directionType::fwd, driveVolt[2], voltageUnits::volt);
    }

    if (driveVolt[3] == 0)
    {
        leftBack.stop(stopBrakeType);
    }
    else
    {
        leftBack.spin(directionType::fwd, driveVolt[3], voltageUnits::volt);
    }
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
