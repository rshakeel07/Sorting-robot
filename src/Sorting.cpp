#include "vex.h"

using namespace vex;

// moves forward from startX with the claw at the top until it finds an empty stretch
// wide enough for a box plus BUFFER on each side
// returns the x of the centre of that spot (mm), or -1 if the rail ends first
double findspot(double startX, double &x_cur, double &y_cur)
{
    double spaceNeeded = BOXWIDTH + 2 * BUFFER;
    double spot = -1;

    if (startX + spaceNeeded <= XMAX) // only search if a box could still fit before the end of the rail
    {
        moveto(startX, 0, x_cur, y_cur, SPEED);

        double clearStart = startX; // where the current empty stretch began
        xMotor.spin(forward, SCANSPEED, percent);
        while (xMotor.position(turns) / CONVERSION_X - clearStart < spaceNeeded && !Bumper7.pressing())
        {
            if (Distance4.objectDistance(mm) < SCANHEIGHT - BOXTHRESHOLD) // something is in the way
            {
                clearStart = xMotor.position(turns) / CONVERSION_X; // the empty stretch can only start after it
            }
        }
        xMotor.stop(brake);

        x_cur = xMotor.position(turns) / CONVERSION_X;
        if (x_cur > XMAX)
        {
            x_cur = XMAX;
        }

        if (x_cur - clearStart >= spaceNeeded)
        {
            spot = clearStart + BUFFER + BOXWIDTH / 2.0;
        }
    }

    return spot;
}

// sorts the boxes from shortest to tallest, then moves each one into its zone on the rail
// the rail is split into m equal zones: the shortest box goes in zone 1, the tallest in zone m
// returns false if there are no boxes or a box can't find a spot
bool sorting(double boxes[ARRLENGTH][2], int m, double &x_cur, double &y_cur)
{
    // bubble sort by height (column 1), swapping x (column 0) along with it so each pair stays together
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < m - 1 - i; j++)
        {
            if (boxes[j][1] > boxes[j + 1][1])
            {
                double tempX = boxes[j][0];
                double tempHeight = boxes[j][1];
                boxes[j][0] = boxes[j + 1][0];
                boxes[j][1] = boxes[j + 1][1];
                boxes[j + 1][0] = tempX;
                boxes[j + 1][1] = tempHeight;
            }
        }
    }

    bool placed = m > 0;
    double lastEdge = 0; // right edge of the last box placed, so the next box never goes behind it

    for (int i = 0; i < m && placed; i++)
    {
        double zoneStart = i * ((double)XMAX / m);
        double searchStart = zoneStart;
        if (lastEdge > searchStart)
        {
            searchStart = lastEdge;
        }

        // find the spot first, while the claw is empty, so the sensor only sees boxes on the table
        double dropX = findspot(searchStart, x_cur, y_cur);
        if (dropX < 0)
        {
            placed = false;
        }
        else
        {
            pickupandplace(boxes[i][0], boxes[i][1], x_cur, y_cur, dropX, YMAX - boxes[i][1]);
            lastEdge = dropX + BOXWIDTH / 2.0;
        }
    }

    return placed;
}
