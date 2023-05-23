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
    double turnImportance = 0.5;
    double headingTransVal = 0;
    double sideTransVal = 0;
    double turnVal = 0;
    double motorVolt[4] = {0};

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

    //Give motors voltage values to run at

    //rightFront.spin (fwd, rightFrontVoltage, volt);
    // rightBack.spin  (fwd, rightBackVoltage, volt);
    // leftFront.spin  (fwd, leftFrontVoltage, volt);
    // leftBack.spin   (fwd, leftBackVoltage, volt);
    motorVolt[0] = rightFrontVoltage;
    motorVolt[1] = leftFrontVoltage;
    motorVolt[2] = rightBackVoltage;
    motorVolt[3] = leftBackVoltage;
    Chassis::getInstance()->setDriveVolt(motorVolt);
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
    TurnTo(90);
    turnFlag = true;
  }

}