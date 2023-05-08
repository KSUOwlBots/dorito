#include "vex.h"
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

    rightFront.spin (fwd, rightFrontVoltage, volt);
    rightBack.spin  (fwd, rightBackVoltage, volt);
    leftFront.spin  (fwd, leftFrontVoltage, volt);
    leftBack.spin   (fwd, leftBackVoltage, volt);
}


void armOPControl(){
    if(master.ButtonL1.pressing()){
      arm.spin(fwd, 12, volt);
    }
    else if(master.ButtonL2.pressing()){
      arm.spin(reverse, 12, volt);
    }
    else{
      arm.stop(brake);
    }
}

void intakeOPControl(){
    
    if(master.ButtonR1.pressing()){
      intake1.spin(fwd, 12, volt);
      intake2.spin(fwd, 12, volt);
    }
    else if(master.ButtonR2.pressing()){
      intake1.spin(reverse, 12, volt);
      intake2.spin(reverse, 12, volt);
    }
    else{
      intake1.stop();
      intake2.stop();
    }

}