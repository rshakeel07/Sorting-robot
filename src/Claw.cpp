#include "vex.h"

using namespace vex;

void claw (bool open, double speed, double percentage) // moves claw either open or closed, at a specific speed and a percentage of how much to close
{
    const int max = 180; // max claw angle
    double target = (percentage / 100) * max; // calculate target angle based on percentage

    clawMotor.resetPosition(); // measure the move from where the claw is now
    timer clawTimer; // stops the claw if it gets blocked (e.g. by a box) before reaching the target
    clawTimer.clear();
    if (open)
    {
        clawMotor.spin(forward, speed, percent);
        while (clawMotor.position(degrees) < target && clawTimer.time(seconds) < CLAWTIMEOUT)
        {}
    }
    else
    {
        clawMotor.spin(reverse, speed, percent);
        while (clawMotor.position(degrees) > -target && clawTimer.time(seconds) < CLAWTIMEOUT)
        {}
    }
    clawMotor.stop(brake);
}

void clawres() // opens the claw fully for 2 seconds, then sets that as the zero position
{
    clawMotor.spin(forward, SPEED, percent);
    wait(2, seconds);
    clawMotor.stop(brake);
    clawMotor.resetPosition();
}
