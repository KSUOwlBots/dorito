#include "vex.h"

using namespace vex;

void controllerGUI(){
    master.Screen.setCursor(1,1);
    master.Screen.print("UwU pizza");
    master.Screen.clearLine(2);
    master.Screen.setCursor(1,2);
    master.Screen.print("angle: ");
    master.Screen.print(imu.heading(degrees));
    master.Screen.setCursor(1, 3);
    master.Screen.print("profile:" + setDriveProfile());
}

void brainGUI(){
    // Brain.Screen.setCursor(1,1);
    // Brain.Screen.print("beeeg UWU goes here");
    // Brain.Screen.print("\nMommys a little slut");
    // Brain.Screen.print("\nI own a musket for home defense, since that's what the founding fathers intended. Four ruffians break into my house. \"What the devil?\" As I grab my powdered wig and Kentucky rifle. Blow a golf ball sized hole through the first man, he's dead on the spot. Draw my pistol on the second man, miss him entirely because it's smoothbore and nails the neighbors dog. I have to resort to the cannon mounted at the top of the stairs loaded with grape shot, \"Tally ho lads\" the grape shot shreds two men in the blast, the sound and extra shrapnel set off car alarms. Fix bayonet and charge the last terrified rapscallion. He Bleeds out waiting on the police to arrive since triangular bayonet wounds are impossible to stitch up. Just as the founding fathers intended.");
    Brain.Screen.drawImageFromFile("frame_00_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_01_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_02_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_03_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_04_delay-0.04s.png",1,3);//20 more times
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_05_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_06_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_07_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_08_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_09_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_10_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_11_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_12_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_13_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_14_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_15_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_16_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_17_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_18_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_19_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_20_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_21_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_22_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_23_delay-0.04s.png",1,3);
    wait(.04, seconds);
    Brain.Screen.drawImageFromFile("frame_24_delay-0.04s.png",1,3);
    wait(.04, seconds);
}

int setDriveProfile(){
    master.Screen.clearScreen();
    master.Screen.setCursor(1,1);
    master.Screen.print("press any of the letters \nfor your driver profile\npress the up arrow for \na random one");
        if(master.ButtonA.pressing()){
            return 1;
        }
        else if(master.ButtonB.pressing()){
            return 2;
        }
        else if(master.ButtonX.pressing()){
            return 3;
        }
        else if(master.ButtonY.pressing()){
            return 4;
        }
        else if(master.ButtonUp.pressing()){
            return rand() % 4 + 1;
        }
        else{
            return 1;
        }
    
}