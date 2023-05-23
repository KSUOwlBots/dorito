#include "vex.h"
#include <cmath>
#include <iostream>
using namespace vex;
using namespace std;

void TurnTo(double rtarget)
{
  //Defines the varibles used for the turn pid
  double err=0;
  double lasterr=0;
  double speed=0;
  float kp=0.12672*1.4;
  float kd=0.3;
  float ki = 0.0125625;
  double integral = 0;
  float routput = 0;
  
  
  while (true)
  {
    double motorVolt[4] = {0};
  
    //err is the rotation err and it calculated by subtracting the reading from the inertia sensor from the degrees of the rotational target or rtarget
    //the inertial sensor works off of a 360 degree scale, just like a circle, so defining rtarget is like picking what degree on a circle you want your robot to face to
    err=rtarget-imu.heading();

    //if inertial >180 away, change desired value by 360 degrees more or less.
    //for example, instead of turnint 350 right, this logic will instead make you turn 10 left
    if (err>180) 
    {
      err-=360;
    }
    if (err<-180) 
    {
      err+=360;
    }

    //the speed at which the bot should turn it's wheels to turned 
    //to target is equal to the opposite of the interial sensor 
    //gyrorate, or the amount of updates the interial sensor is getting
    //about what direction the bot is facing
    speed=imu.gyroRate(yaxis,dps);
    

    //Updates lasterr to be the current err as err will change in the next cycle and the last err is needed in order to know how far the bot has turned
    // integral +=err;
    // if(abs(err) > 2){
    //   integral = 0;
    // }
    integral += err*(50*50/((50+abs(speed))*(50+abs(speed))));
    // if(abs(err) < 2){
    //   integral = 0;
    // }
    if((lasterr <= 0 && err > 0) || (lasterr >= 0 && err < 0)){
      integral = 0;
    }
    
    lasterr=err;

    //INTERGAL COMMENTS HERE
    // sum +=err;
    // if (abs((rDrive.velocity(percent)+lDrive.velocity(percent))/2) > 50)
    // {
    //   sum = 0;
    // }

    // rtoutput is the voltage that the motors should get based on the err, kp, kd, and speed to get to rtarget
    routput=err*kp+speed*kd+integral*ki;
    





    //tells the wheels to spin at the volatages toutput and routput tell it to spin at
    // lDrive.spin(fwd, routput*1.2, volt);
    // rDrive.spin(fwd, -routput*1.2, volt);
    motorVolt[1] = routput*1.2;
    motorVolt[3] = routput*1.2;
    motorVolt[0] = -routput*1.2;
    motorVolt[4] = -routput*1.2;

    Chassis::getInstance()->setDriveVolt(motorVolt);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    // Brain.Screen.print("Velocity: ");
    // Brain.Screen.print(flyVelocity);
    // Brain.Screen.newLine();
    master.Screen.print("Error: ");
    master.Screen.print(err);
    master.Screen.newLine();
    master.Screen.print("Volts: ");
    master.Screen.print(routput*.12);
    master.Screen.newLine();
    master.Screen.print("Speed: ");
    master.Screen.print(speed);
    // Brain.Screen.newLine();
    // Brain.Screen.print("Integral: ");
    // Brain.Screen.print(integral*ki);
    wait(15,msec);

    //ADD INEGRAL HERE
    if (abs(speed) <= 1 && abs(err) <= 1)
    {
    // // sum = 0;
    // rDrive.stop(brake); lDrive.stop(brake); 
    break;
    }
  }
}