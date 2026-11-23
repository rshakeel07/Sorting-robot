#include "vex.h"

using namespace vex;

// returns true once a scan reaches the end of the rail
// a forward scan ends at the bumper (x = XMAX), a reverse scan ends back at home (x = 0)
bool scanend(bool forwardScan)
{
    if (forwardScan)
    {
        return Bumper7.pressing();
    }
    return xMotor.position(turns) <= 0;
}

// scans along the rail at a constant slow speed with the claw at the top, recording every box it finds
// forwardScan = true scans from home to the bumper, false scans from the bumper back to home
// boxes[i][0] = x of the centre of box i (mm), boxes[i][1] = height of box i (mm)
// returns the number of boxes found (m)
int dataCollection(double boxes[ARRLENGTH][2], bool forwardScan, double &x_cur, double &y_cur)
{
    fillarray(boxes);
    int count = 0;

    moveto(x_cur, 0, x_cur, y_cur, SPEED); // raises the claw to the top before scanning

    if (forwardScan)
    {
        xMotor.spin(forward, SCANSPEED, percent);
    }
    else
    {
        xMotor.spin(reverse, SCANSPEED, percent);
    }

    while (!scanend(forwardScan) && count < ARRLENGTH)
    {
        if (Distance4.objectDistance(mm) < SCANHEIGHT - BOXTHRESHOLD) // front edge of a box
        {
            double startX = xMotor.position(turns) / CONVERSION_X;
            double minDistance = SCANHEIGHT;

            if (boxdetect(minDistance)) // follows the box until its back edge passes
            {
                double endX = xMotor.position(turns) / CONVERSION_X;
                boxes[count][0] = (startX + endX) / 2;      // centre of the box
                boxes[count][1] = SCANHEIGHT - minDistance; // height of the box
                count++;
            }
        }
    }
    xMotor.stop(brake);

    // update the current position from the encoder, keeping it on the rail
    // (the encoder can read slightly past the ends, which would make moveto() refuse to move)
    x_cur = xMotor.position(turns) / CONVERSION_X;
    if (x_cur > XMAX)
    {
        x_cur = XMAX;
    }
    if (x_cur < 0)
    {
        x_cur = 0;
    }

    return count;
}
