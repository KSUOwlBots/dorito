#include "vex.h"
#include <cmath>
#include <iostream>
using namespace vex;
using namespace std;

void TurnTo(double rTarget, double rSpeed)
{
  //Defines the varibles used for the turn pid
  double err=0;
  double lastErr=0;
  double speed=0;
  float kp=0.12672*1.4;
  float kd=0.03;
  float ki = 0.0125625;
  double integral = 0;
  float rOutput = 0;
  
  
  while (true)
  {
    double motorVolt[4];
  
    //err is the rotation err and it calculated by subtracting the reading from the inertia sensor from the degrees of the rotational target or rtarget
    //the inertial sensor works off of a 360 degree scale, just like a circle, so defining rtarget is like picking what degree on a circle you want your robot to face to
    err=rTarget-imu.heading();

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
    speed=imu.gyroRate(xaxis,dps);
    

    //Updates lasterr to be the current err as err will change in the next cycle and the last err is needed in order to know how far the bot has turned
    // integral +=err;
    // if(abs(err) > 2){
    //   integral = 0;
    // }
    integral += err*(50*50/((50+abs(speed))*(50+abs(speed))));
    // if(abs(err) < 2){
    //   integral = 0;
    // }
    if((lastErr <= 0 && err > 0) || (lastErr >= 0 && err < 0)){
      integral = 0;
    }
    
    lastErr=err;

    //INTERGAL COMMENTS HERE
    // sum +=err;
    // if (abs((rDrive.velocity(percent)+lDrive.velocity(percent))/2) > 50)
    // {
    //   sum = 0;
    // }

    // rtoutput is the voltage that the motors should get based on the err, kp, kd, and speed to get to rtarget
    rOutput=err*kp+speed*kd+integral*ki;
    

    //tells the wheels to spin at the volatages toutput and routput tell it to spin at
    // lDrive.spin(fwd, routput*1.2, volt);
    // rDrive.spin(fwd, -routput*1.2, volt);
    motorVolt[1] = rOutput*1.2*rSpeed;
    motorVolt[3] = rOutput*1.2*rSpeed;
    motorVolt[0] = -rOutput*1.2*rSpeed;
    motorVolt[2] = -rOutput*1.2*rSpeed;
    Chassis::getInstance()->setDriveVolt(motorVolt);
    master.Screen.clearScreen();
    master.Screen.setCursor(1, 1);
    // Brain.Screen.print("Velocity: ");
    // Brain.Screen.print(flyVelocity);
    // Brain.Screen.newLine();
    master.Screen.print("Error: ");
    master.Screen.print(err);
    master.Screen.newLine();
    master.Screen.print("Volts: ");
    master.Screen.print(rOutput*.12);
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

void DriveTo(int target, double intake = 15, double errThres = 3, int rtarget=imu.heading())
{
  
  //Defines the varibles used for the drive pid
  double Terr;
  double Tlasterr=0;
  double Tspeed;
  float Tkp=0.0384;
  float Tkd=0.05;
  float Tki = 0.0012;
  double toutput = 0;
  double motorPosition = 0;
  double tIntegral = 0;

  //Defines the varibles used for the turing pid
  double err = 0  ;
  double lasterr=0;
  double speed = 0;
  float kp=0.38016;
  float kd=0.3;
  float ki = 0.0125625;
  double routput = 0;
  double integral = 0;



  //Resets the position reading on all of the motors to get more accurate readings
  leftFront.setPosition(0,degrees);
  rightFront.setPosition(0,degrees);



  while (true)
  {
    double motorVolt[4];

    //Compares the position readings for the left and right wheels and takes the lower reading in order to not over shoot
    //motorPosition is used to calculcate the Terr
    if ((rightFront.position(degrees)) > ((leftFront.position(degrees)))) 
    {
      motorPosition = leftFront.position(degrees);
    }
    else 
    {
      motorPosition = rightFront.position(degrees);
    }



    //Terr is calculated as the difference between the target distance and motorPosition
    Terr=target-motorPosition;

    //Tspeed is calculated from the difference in Terr and Tlasterr, so the further away the bot is from its target, the faster the bot will go
    Tspeed = Terr-Tlasterr;

    //Updates Tlasterr to be the current Terr as Terr will change in the next cycle and the last Terr is needed in order to know how far the bot has traveled
    Tlasterr=Terr;
    if(abs(Terr) < 75){
      tIntegral += Terr; 
    }
    if((Tlasterr <= 0 && Terr > 0) || (Tlasterr >= 0 && Terr < 0)){
      tIntegral = 0;
    }
    //toutput is the voltage that the motors should get based on the Terr, Tkp, Tkd, and Tspeed to get to target
    toutput=Terr*Tkp+Tspeed*Tkd + tIntegral*Tki;
    


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



    //the speed at which the bot should turn it's wheels to turned to target is equal to the opposite of the interial sensor gyrorate, or the amount of updates the interial sensor is getting
    //about what direction the bot is facing
    speed=imu.gyroRate(xaxis,dps);
    
    //Updates lasterr to be the current err as err will change in the next cycle and the last err is needed in order to know how far the bot has turned
    if(abs(Terr) < 10){
      integral += err*(50*50/((50+abs(speed))*(50+abs(speed)))); 
    }
    
    
    if((lasterr <= 0 && err > 0) || (lasterr >= 0 && err < 0)){
      integral = 0;
    }

    //rtoutput is the voltage that the motors should get based on the err, kp, kd, and speed to get to rtarget
    routput=err*kp+speed*kd + integral*ki;


      toutput = clamp(toutput, -1*(intake), intake);
    //This if statement logic makes it so that if toutput is either giving the motors more than 11 volts or less than -11 volts, toutpout should be 11 or -11 respectively.
    //This allows routput to give the motors either 12 volts or -12 volts to turn.
    if (toutput > 11) 
    {
      toutput = 11;
    }
    if (toutput < -11) 
    {
      toutput = -11;
    }



    //routput = 0;
    //tells the wheels to spin at the volatages toutput and routput tell it to spin at
    // lDrive.spin(fwd, (toutput+1 + routput*1.2), volt);
    // rDrive.spin(fwd, (toutput+1 - routput*1.2), volt);
    motorVolt[1] = toutput+1 + routput*1.2;
    motorVolt[3] = toutput+1 + routput*1.2;
    motorVolt[0] = toutput+1 - routput*1.2;
    motorVolt[2] = toutput+1 - routput*1.2;
    Chassis::getInstance()->setDriveVolt(motorVolt);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("TSpeed: ");
    Brain.Screen.print(Tspeed);
    Brain.Screen.newLine();
    Brain.Screen.print("TError: ");
    Brain.Screen.print(Terr);
    Brain.Screen.newLine();
    Brain.Screen.print("RSpeed: ");
    Brain.Screen.print(speed);
    Brain.Screen.newLine();
    Brain.Screen.print("RError: ");
    Brain.Screen.print(err);
    wait(15, msec);


    //ADD INEGRAL HERE
    if (abs(speed*2) <= 1 && abs(err) <= 1 && abs(Tspeed*2) <= errThres && abs(Terr) <= 30)
    {

    //   rDrive.stop(brake);
    //   lDrive.stop(brake);
      break;
    }
  }
}
