#include "vex.h"

using namespace vex;

// moves the claw to (x_tar, y_tar), then updates x_cur / y_cur (passed by reference so the caller sees the new position)
// uses the motor encoders' absolute positions, which calibrateGantry() zeroes at home (0, 0)
void moveto(double x_tar, double y_tar, double &x_cur, double &y_cur, double speed)
{
    // only move if the target is inside the gantry
    if (x_tar >= 0 && x_tar <= XMAX && y_tar >= 0 && y_tar <= YMAX)
    {
        double x_turns = x_tar * CONVERSION_X;
        double y_turns = y_tar * CONVERSION_Y; // x / y targets are now in motor turns

        // move x
        if (x_tar > x_cur)
        {
            xMotor.spin(forward, speed, percent);
            while (xMotor.position(turns) < x_turns)
            {}
        }
        else if (x_tar < x_cur)
        {
            xMotor.spin(reverse, speed, percent);
            while (xMotor.position(turns) > x_turns)
            {}
        }
        xMotor.stop(brake);

        // then move y
        if (y_tar > y_cur)
        {
            yMotor.spin(forward, speed, percent);
            while (yMotor.position(turns) < y_turns)
            {}
        }
        else if (y_tar < y_cur)
        {
            yMotor.spin(reverse, speed, percent);
            while (yMotor.position(turns) > y_turns)
            {}
        }
        yMotor.stop(brake);

        x_cur = x_tar;
        y_cur = y_tar;
    }
}
