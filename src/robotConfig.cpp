#include "vex.h"
#include <iostream>

using namespace vex;

brain  Brain;


//controller
controller master = controller(primary);
inertial imu = inertial(PORT16);
//drivetrain
motor leftFront1 = motor(PORT10, ratio18_1);
motor leftFront2 = motor(PORT1, ratio18_1);
motor_group leftFront = motor_group(leftFront1, leftFront2);

motor leftBack1 = motor(PORT2, ratio18_1);
motor leftBack2 = motor(PORT3, ratio18_1);
motor_group leftBack = motor_group(leftBack1, leftBack2);

motor rightFront1 = motor(PORT20, ratio18_1);
motor rightFront2 = motor(PORT4, ratio18_1);
motor_group rightFront = motor_group(rightFront1, rightFront2);

motor rightBack1 = motor(PORT11, ratio18_1);
motor rightBack2 = motor(PORT5, ratio18_1);
motor_group rightBack = motor_group(rightBack1, rightBack2);






//e
digital_out clawPiston = digital_out(Brain.ThreeWirePort.A);
digital_out climbPiston = digital_out(Brain.ThreeWirePort.B);

//other motors
motor arm = motor(PORT20, true);
motor winch = motor(PORT17, true);






// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}