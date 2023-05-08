using namespace vex;

extern brain Brain;


//controller
extern controller master;

//drivetrain

extern motor_group leftFront;
extern motor_group leftBack;
extern motor_group rightFront;
extern motor_group rightBack;

//other motors
extern motor arm;
extern motor intake1;
extern motor intake2;



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );