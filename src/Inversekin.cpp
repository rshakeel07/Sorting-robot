#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

#define CONVERSION_X 1 // arbitrary value for conversion factor of distance to motor turns
#define CONVERSION_Y 1 // same but for y

void moveto(double x_tar, double y_tar, double x_cur, double y_cur, double speed)
{
    double delta_x = (x_tar - x_cur) * CONVERSION_X;
    double delta_y = (y_tar - y_cur) * CONVERSION_Y; // x / y values are now put into turns of x / y

    xMotor.spinFor(forward, delta_x, turns, speed, percent, true);
    yMotor.spinFor(forward, delta_y, turns, speed, percent, true); // the true makes it so that the next command is only done after this one is completed

    x_cur = x_tar;
    y_cur = y_tar;
}