#include "vex.h"

using namespace vex;

void controllerGUI(){
    master.Screen.clearScreen();
    master.Screen.setCursor(1,1);
    master.Screen.print("UwU");
    master.Screen.print("\nPizza");
}

void brainGUI(){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("beeeg UWU goes here");
    Brain.Screen.print("\nMommys a little slut");
    Brain.Screen.print("\nhelloo");
    Brain.Screen.drawImageFromFile("ehe.png", 1, 3);
}