#include "vex.h"

using namespace vex;

// raises the claw, returns home, stops every motor and ends the program
void shutdown(double &x_cur, double &y_cur)
{
    moveto(x_cur, 0, x_cur, y_cur, SPEED); // raise the claw first (moveto moves x before y, so going straight home could drag the claw through the boxes)
    moveto(0, 0, x_cur, y_cur, SPEED);     // then go home

    xMotor.stop(brake);
    yMotor.stop(brake);
    clawMotor.stop(brake);

    // keep the message on the screen until the Touch LED is pressed
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Press LED to end");
    while (!TouchLED9.pressing())
    {}
    Brain.programStop();
}
