#include "vex.h"

using namespace vex;

// picks up the box at xbox (height ybox), carries it to x_tar and drops it at height y_tar
// (y_tar = 0 drops it from the top; y_tar = YMAX - ybox lowers it to the table first)
void pickupandplace(double xbox, double ybox, double &x_cur, double &y_cur, double x_tar, double y_tar)
{
    moveto(xbox, YMAX - ybox, x_cur, y_cur, SPEED); // moves to right above the block
    claw(false, SPEED, CLAWCLOSE); // closes claw around box
    moveto(x_cur, 0, x_cur, y_cur, SPEED); // lifts box straight up
    moveto(x_tar, y_tar, x_cur, y_cur, SPEED); // moves to target x / y coordinates
    claw(true, SPEED, CLAWCLOSE); // opens claw
    moveto(x_cur, 0, x_cur, y_cur, SPEED); // raises claw back to the top
}


// goes to pos of box in x
// lowers down to height
// grips the box closing claw depending on the width of the box (OR COULD BE JUST A GENEARL HARD CODED AMOUNT)
// the gantry moves back up to default height
