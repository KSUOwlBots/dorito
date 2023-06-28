#include "vex.h"
//#include "drivetrain.h"
#include <cmath>
#include <iostream>
using namespace vex;
using namespace std;


Chassis::Chassis(float activeBrake, float leftTrackerDiameter, float leftTrackerCenterDistance, float rightTrackerDiameter, float rightTrackerCenterDistacne) :
    activeBrakekp(activeBrake),
    leftTrackerCenterDistance(leftTrackerCenterDistance),
    leftTrackerDiameter(leftTrackerDiameter),
    leftTrackerInToDegRatio(leftTrackerDiameter * M_PI / 360),
    rightTrackerCenterDistance(rightTrackerCenterDistacne),
    rightTrackerDiameter(rightTrackerDiameter),
    rightTrackerInToDegRatio(rightTrackerDiameter * M_PI / 360)
    {
        stopBrakeType = brake;
        odom.set_physical_distances(leftTrackerCenterDistance, rightTrackerCenterDistance);
        odom_task = task(position_track_task);
        set_coordinates(0,0,0);
    }
    Chassis::Chassis(){
        stopBrakeType = brake;
        activeBrakekp =.3;
    }
/*
Chassis(float activeBrake, float leftTrackerDiameter, float leftTrackerCenterDistance, float rightTrackerDiameter, float rightTrackerCenterDistacne);
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
  return(imu.heading()); 
}
float Chassis::getLeftTrackerPos(){
    return (leftTracker.position(deg)*leftTrackerInToDegRatio);
}
float Chassis::getRightTrackerPos(){
    return (rightTracker.position(deg)*rightTrackerInToDegRatio);
}
void Chassis::position_track(){
    odom.update_position(getLeftTrackerPos(), getRightTrackerPos(), odom.orientation_deg);
}
void Chassis::set_coordinates(float X_position, float Y_position, float orientation_deg){
    odom.set_position(X_position, Y_position, orientation_deg, getLeftTrackerPos(), getRightTrackerPos());
}
int Chassis::position_track_task(){
  chassis.position_track();
  return(0);
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
        rightFront.spin(directionType::fwd, driveVolt[0], voltageUnits::volt);
    }
    else
    {
        rightFront.spin(directionType::fwd, driveVolt[0], voltageUnits::volt);
    }

    if (driveVolt[1] == 0)
    {
        leftFront.stop(stopBrakeType);
        leftFront.spin(directionType::fwd, driveVolt[1], voltageUnits::volt);
    }
    else
    {
        leftFront.spin(directionType::fwd, driveVolt[1], voltageUnits::volt);
    }

    if (driveVolt[2] == 0)
    {
        rightBack.stop(stopBrakeType);
        rightBack.spin(directionType::fwd, driveVolt[2], voltageUnits::volt);
    }
    else
    {
        rightBack.spin(directionType::fwd, driveVolt[2], voltageUnits::volt);
    }

    if (driveVolt[3] == 0)
    {
        leftBack.stop(stopBrakeType);
        leftBack.spin(directionType::fwd, driveVolt[3], voltageUnits::volt);
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
