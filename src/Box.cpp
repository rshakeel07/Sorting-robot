#include "vex.h"

using namespace vex;

bool boxdetect()
{
    if (Distance4.objectDistance(mm) < YMAX - 5)
    {
        return true;
    }
    return false;
}

void nobox()
{
    wait(30, seconds);
    // SCAN FUNCTION NEED TO WAIT FOR SOMEONE TO DO THAT
}
