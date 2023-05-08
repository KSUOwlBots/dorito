#include "vex.h"
#include <cmath>
// #include "strings.h"
// #include <fstream>
// #include <iostream>
using namespace vex;
using namespace std;

void driveOPControl(){
    double headingTransVal = master.Axis3.position();
    double sideTransVal = master.Axis4.position();
    double turnVal = master.Axis1.position();

    //convert controller input into voltage inputs  
    double forwardVolts = headingTransVal * 0.12;
    double strafeVolts = sideTransVal * 0.12;
    double turnVolts = turnVal * 0.12;    

    //Give motors voltage values to run at

    rightFront.spin (fwd, - forwardVolts + strafeVolts + turnVolts, volt);
    rightBack.spin  (fwd, - forwardVolts - strafeVolts + turnVolts, volt);
    leftFront.spin  (fwd, + forwardVolts + strafeVolts + turnVolts, volt);
    leftBack.spin   (fwd, + forwardVolts - strafeVolts + turnVolts, volt);
}