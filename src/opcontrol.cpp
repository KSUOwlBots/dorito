#include "vex.h"
#include "drive/chassis.h"
#include <cmath>
// #include "strings.h"
// #include <fstream>
// #include <iostream>
using namespace vex;
using namespace std;

void driveOPControl(){
    
    double deadzone = 5;
    double maxVoltage = 12.0;
    double turnImportance = 0.5;
    double headingTransVal = 0;
    double sideTransVal = 0;
    double turnVal = 0;
    double motorVolt[4] = {0,0,0,0};

    if(abs(master.Axis3.position()) >= deadzone){
        headingTransVal = master.Axis3.position();
    }
    if(abs(master.Axis4.position()) >= deadzone){
        sideTransVal = master.Axis4.position();
    }
    if(abs(master.Axis1.position()) >= deadzone){
        turnVal = master.Axis1.position();
    }


    //convert controller input into voltage inputs  
    double turnVolts = turnVal * 0.12;
    double forwardVolts = headingTransVal * 0.12 * (1 - (abs(turnVolts)/12.0) * turnImportance);
    double strafeVolts = sideTransVal * 0.12 * (1 - (abs(turnVolts)/12.0) * turnImportance);

    //set voltages for each motor
    double rightFrontVoltage = + forwardVolts - strafeVolts + turnVolts;
    double rightBackVoltage = + forwardVolts + strafeVolts + turnVolts;
    double leftFrontVoltage = - forwardVolts - strafeVolts + turnVolts;
    double leftBackVoltage = - forwardVolts + strafeVolts + turnVolts;
    

    double xSpeed = clamp(headingTransVal, -1.0, 1.0);
    if (std::abs(xSpeed) < deadzone) {
      xSpeed = 0;
    }

    double ySpeed = -clamp(sideTransVal, -1.0, 1.0);
    if (std::abs(ySpeed) < deadzone) {
      ySpeed = 0;
    }

    double yaw = clamp(turnVal, -1.0, 1.0);
    if (std::abs(yaw) < deadzone) {
      yaw = 0;
    }
    double fwd = xSpeed * cos((imu).heading()) - ySpeed * sin((imu).heading());
    double right = xSpeed * sin((imu).heading()) + ySpeed * cos((imu).heading());

    

    //Give motors voltage values to run at

    //rightFront.spin (fwd, rightFrontVoltage, volt);
    // rightBack.spin  (fwd, rightBackVoltage, volt);
    // leftFront.spin  (fwd, leftFrontVoltage, volt);
    // leftBack.spin   (fwd, leftBackVoltage, volt);
    //for chassis object
    // motorVolt[0] = rightFrontVoltage;
    // motorVolt[1] = leftFrontVoltage;
    // motorVolt[2] = rightBackVoltage;
    // motorVolt[3] = leftBackVoltage;
    //old chassis constructor for movement
    // Chassis::getInstance()->setDriveVolt(motorVolt);

    motorVolt[0] = (clamp(fwd + right - yaw, -1.0, 1.0) * maxVoltage);
    motorVolt[1] = (clamp(fwd - right + yaw, -1.0, 1.0) * maxVoltage);
    motorVolt[2] = (clamp(fwd - right - yaw, -1.0, 1.0) * maxVoltage);
    motorVolt[3] = (clamp(fwd + right + yaw, -1.0, 1.0) * maxVoltage);
    
    chassis.setDriveVolt(motorVolt);
}


void armOPControl(){
    bool armUp = master.ButtonL1.pressing();
    bool armDown = master.ButtonL2.pressing();
    if(armUp){
      arm.spin(fwd, 12, volt);
    }
    else if(armDown){
      arm.spin(reverse, 12, volt);
    }
    else{
      arm.stop(brake);
    }
}

void clawOPControl(){
    bool clawClose = master.ButtonR1.pressing();
    bool clawOpen = master.ButtonR2.pressing();
    ///////////////////////////
    //claw control
    ///////////////////////////
    if(clawClose){
      clawPiston.set(false);
    }
    else if(clawOpen){
      clawPiston.set(true);
    }

}


void winchOPControl(){
    bool winchUp = master.ButtonUp.pressing();
    bool winchDown = master.ButtonDown.pressing();
    if(winchUp){
      climbPiston.set(false);
    }
    else if(winchDown){
      climbPiston.set(true);
    }
}

void driveMacros(){
  bool turnFlag = true;
  if(master.ButtonX.pressing()){
    turnFlag = false;
  }
  if(turnFlag == false){
    TurnTo(0, 1);
    turnFlag = true;
  }

}






/*
void XDriveModel::fieldOrientedXArcade(double ixSpeed,
                                       double iySpeed,
                                       double iyaw,
                                       QAngle iangle,
                                       double ithreshold) {
  double xSpeed = std::clamp(ixSpeed, -1.0, 1.0);
  if (std::abs(xSpeed) < ithreshold) {
    xSpeed = 0;
  }

  double ySpeed = -std::clamp(iySpeed, -1.0, 1.0);
  if (std::abs(ySpeed) < ithreshold) {
    ySpeed = 0;
  }

  double yaw = std::clamp(iyaw, -1.0, 1.0);
  if (std::abs(yaw) < ithreshold) {
    yaw = 0;
  }

  double fwd = xSpeed * cos(iangle).getValue() - ySpeed * sin(iangle).getValue();
  double right = xSpeed * sin(iangle).getValue() + ySpeed * cos(iangle).getValue();

  topLeftMotor->moveVoltage(
    static_cast<int16_t>(std::clamp(fwd - right + yaw, -1.0, 1.0) * maxVoltage));
  topRightMotor->moveVoltage(
    static_cast<int16_t>(std::clamp(fwd + right - yaw, -1.0, 1.0) * maxVoltage));
  bottomRightMotor->moveVoltage(
    static_cast<int16_t>(std::clamp(fwd - right - yaw, -1.0, 1.0) * maxVoltage));
  bottomLeftMotor->moveVoltage(
    static_cast<int16_t>(std::clamp(fwd + right + yaw, -1.0, 1.0) * maxVoltage));
}
*/