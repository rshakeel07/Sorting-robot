#include "vex.h"

using namespace vex;

// called at the front edge of a box while the carriage is already moving at SCANSPEED
// keeps going until the back edge of the box passes, recording the smallest distance reading (the top of the box) in minDistance
// returns false if the box takes longer than BOXTIMEOUT to pass (a false trigger or something that isn't a box)
bool boxdetect(double &minDistance)
{
    timer boxTimer;
    boxTimer.clear();
    minDistance = Distance4.objectDistance(mm);

    // stays in the loop while something is under the sensor, unless it takes too long or the carriage reaches either end of the rail
    while (Distance4.objectDistance(mm) < SCANHEIGHT - BOXTHRESHOLD && boxTimer.time(seconds) < BOXTIMEOUT &&
           !Bumper7.pressing() && xMotor.position(turns) >= 0)
    {
        double reading = Distance4.objectDistance(mm);
        if (reading < minDistance)
        {
            minDistance = reading;
        }
    }

    return boxTimer.time(seconds) < BOXTIMEOUT;
}

void nobox()
{
    wait(30, seconds);
    // SCAN FUNCTION NEED TO WAIT FOR SOMEONE TO DO THAT
}
