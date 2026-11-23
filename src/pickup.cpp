#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

#define CONVERSION_X 1 // arbitrary value for conversion factor of distance to motor turns
#define CONVERSION_Y 1 // same but for y
#define MOTORSPEED 1 // arbitrary motor speed percentage
#define BOXWIDTH 1 // box width for closing grippers
#define XMAX 1 //max x length
#define YMAX 1 // max y height

void moveto(double x_tar, double y_tar, double x_cur, double y_cur, double speed)
{
    double delta_x = (x_tar - x_cur) * CONVERSION_X;
    double delta_y = (y_tar - y_cur) * CONVERSION_Y; // x / y values are now put into turns of x / y

    xMotor.spinFor(forward, delta_x, turns, speed, percent, true);
    yMotor.spinFor(forward, delta_y, turns, speed, percent, true); // the true makes it so that the next command is only done after this one is completed

    x_cur = x_tar;
    y_cur = y_tar;
}

void pickupandplace(double xbox, double ybox, double x_cur, double y_cur, double x_tar, double y_tar) // picks up box and brings it back up, 
{
    moveto(xbox, YMAX - ybox, x_cur, y_cur, MOTORSPEED); // moves to right above the block
    claw(false, MOTORSPEED, BOXWIDTH); // closes claw around box
    moveto(x_cur, 0, x_cur, y_cur, MOTORSPEED); // picks up box one more time
    moveto(x_tar, YMAX - ybox, x_cur, y_cur, MOTORSPEED); // moves to target x / y coordinates (depending on if we change y_tar to 0 or as is it will either drop it where it wants or from top)
    claw(true, MOTORSPEED, BOXWIDTH); //opens claw
}


// goes to pos of box in x
// lowers down to height
// grips the box closing claw depending on the width of the box (OR COULD BE JUST A GENEARL HARD CODED AMOUNT)
// the gantry moves back up to default height

