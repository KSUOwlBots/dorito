#include "vex.h"
#include "drive/chassis.h"
#include <cmath>
// #include "strings.h"
// #include <fstream>
// #include <iostream>
using namespace vex;
using namespace std;

void driveOPControl(){
    //controller deadzone
    double deadzone = 5;
    //code deadzone
    double deadband = .05;
    //max voltage motors can run
    double maxVoltage = 12.0;
    //smother turns
    double turnImportance = 0.5;
    //yes.
    double headingTransVal = 0;
    //yes.
    double sideTransVal = 0;
    //yes.
    double turnVal = 0;
    //init. motor volt array
    double motorVolt[4] = {0,0,0,0};

    ///////////////////////////////////////////////
    //get controller input
    ///////////////////////////////////////////////
    //move fwd/backwards
    if(abs(master.Axis3.position()) >= deadzone){
        headingTransVal = master.Axis3.position();
        headingTransVal = headingTransVal/100;
    }
    //move left/right
    if(abs(master.Axis4.position()) >= deadzone){
        sideTransVal = master.Axis4.position();
        sideTransVal = sideTransVal/100;
    }
    //turn
    if(abs(master.Axis1.position()) >= deadzone){
        turnVal = master.Axis1.position();
        turnVal = turnVal/100;
    }


    //convert controller input into voltage inputs  
    double turnVolts = turnVal * 12;
    double forwardVolts = headingTransVal * 12 * (1 - (abs(turnVolts)*12.0) * turnImportance);
    double strafeVolts = sideTransVal * 12 * (1 - (abs(turnVolts)*12.0) * turnImportance);

    // //set voltages for each motor
    // double rightFrontVoltage = + forwardVolts - strafeVolts + turnVolts;
    // double rightBackVoltage = + forwardVolts + strafeVolts + turnVolts;
    // double leftFrontVoltage = - forwardVolts - strafeVolts + turnVolts;
    // double leftBackVoltage = - forwardVolts + strafeVolts + turnVolts;
    


    ///////////////////////////////////////////////////////////////////////////////////
    //for field oriented x/mechanum drive
    ///////////////////////////////////////////////
    //set x speed
    double xSpeed = clamp(headingTransVal, -1.0, 1.0);
    if (std::abs(xSpeed) < deadband) {
      xSpeed = 0;
    }
    //set y speed
    double ySpeed = -clamp(sideTransVal, -1.0, 1.0);
    if (std::abs(ySpeed) < deadband) {
      ySpeed = 0;
    }
    //set turn speed
    double yaw = clamp(turnVal, -1.0, 1.0);
    if (std::abs(yaw) < deadband) {
      yaw = 0;
    }

    //GET THIS IN RADIANS DUMMY
    // double fwd = xSpeed * cos((imu).heading()) - ySpeed * sin((imu).heading());
    // double right = xSpeed * sin((imu).heading()) + ySpeed * cos((imu).heading());

    double fwd = xSpeed * cos(deg2rad(-(imu).heading())) + ySpeed * sin(deg2rad(-(imu).heading()));
    double right = xSpeed * sin(deg2rad(-(imu).heading())) - ySpeed * cos(deg2rad(-(imu).heading()));
    double rightFrontVoltage = (clamp(+fwd - right + yaw, -1.0, 1.0) * maxVoltage);
    double leftFrontVoltage = (clamp(-fwd - right + yaw, -1.0, 1.0) * maxVoltage);
    double rightBackVoltage = (clamp(+fwd + right + yaw, -1.0, 1.0) * maxVoltage);
    double leftBackVoltage = (clamp(-fwd + right + yaw, -1.0, 1.0) * maxVoltage);





    ///////////////////////////////////////////////////////////////////////////////////
    //for using without chassis object
    ///////////////////////////////////////////////
    //Give motors voltage values to run at
    //rightFront.spin (fwd, rightFrontVoltage, volt);
    // rightBack.spin  (fwd, rightBackVoltage, volt);
    // leftFront.spin  (fwd, leftFrontVoltage, volt);
    // leftBack.spin   (fwd, leftBackVoltage, volt);
    

    // switch(setDriveProfile()){
    //   case 1:
    //   motorVolt[0] = (clamp(fwd + right - yaw, -1.0, 1.0) * maxVoltage);
    //   motorVolt[1] = (clamp(fwd - right + yaw, -1.0, 1.0) * maxVoltage);
    //   motorVolt[2] = (clamp(fwd - right - yaw, -1.0, 1.0) * maxVoltage);
    //   motorVolt[3] = (clamp(fwd + right + yaw, -1.0, 1.0) * maxVoltage);
    //     break;
    //   case 2:
    //   fwd = xSpeed * cos((imu).heading()) - ySpeed * sin((imu).heading());
    //   right = xSpeed * sin((imu).heading()) + ySpeed * cos((imu).heading());
    //   motorVolt[0] = (clamp(fwd + right - yaw, -1.0, 1.0) * maxVoltage);
    //   motorVolt[1] = (clamp(fwd - right + yaw, -1.0, 1.0) * maxVoltage);
    //   motorVolt[2] = (clamp(fwd - right - yaw, -1.0, 1.0) * maxVoltage);
    //   motorVolt[3] = (clamp(fwd + right + yaw, -1.0, 1.0) * maxVoltage);
    //     break;
  //   //   case 3:
  //   double   rightFrontVoltage = + forwardVolts - strafeVolts + turnVolts;
  //  double rightBackVoltage = + forwardVolts + strafeVolts + turnVolts;
  //  double  leftFrontVoltage = - forwardVolts - strafeVolts + turnVolts;
  //  double  leftBackVoltage = - forwardVolts + strafeVolts + turnVolts;
      
    //     break;
    // }

    ///////////////////////////////////////////////////////////////////////////////////
    //give the motor voltage array the values to run at
    ///////////////////////////////////////////////
    motorVolt[0] = rightFrontVoltage;
    motorVolt[1] = leftFrontVoltage;
    motorVolt[2] = rightBackVoltage;
    motorVolt[3] = leftBackVoltage;

    //chassis object set drive voltage to the motor voltage array
    //Chassis::getInstance()->setDriveVolt(motorVolt);
    chassis.setDriveVolt(motorVolt);
    chassis.chassisRun();

    
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
  // bool turnFlag = true;
  // if(master.ButtonX.pressing()){
  //   turnFlag = false;
  // }
  // if(turnFlag == false){
  //   TurnTo(0, 1);
  //   turnFlag = true;
  // }

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