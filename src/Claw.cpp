#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

void claw (bool open, double speed, double percentage) // moves claw either open or closed, at a specific speed and a percentage of how much to close
{
    const int max = 180; // max claw angle
    double target = (percentage / 100) * max; // calculate target angle based on percentage
    directionType dir = open ? forward : reverse;

    clawMotor.spinFor(dir, target, degrees, speed, percent);
}

void clawres()
{
    clawMotor.resetPosition();
    
}