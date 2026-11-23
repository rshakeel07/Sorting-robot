#include "vex.h"

using namespace vex;

// goes home, scans the rail again and checks that the boxes are now sorted
// returns true if it finds exactly m boxes and each one is at least as tall as the one before it
// (heights within HEIGHTTOLERANCE count as equal, to allow for sensor jitter)
bool verifysort(int m, double &x_cur, double &y_cur)
{
    double verifyBoxes[ARRLENGTH][2];

    moveto(x_cur, 0, x_cur, y_cur, SPEED); // raise the claw first so it doesn't drag through the boxes
    moveto(0, 0, x_cur, y_cur, SPEED);     // then go home
    int verifyCount = dataCollection(verifyBoxes, true, x_cur, y_cur);

    bool inOrder = verifyCount == m;
    for (int i = 0; i < verifyCount - 1 && inOrder; i++)
    {
        if (verifyBoxes[i][1] > verifyBoxes[i + 1][1] + HEIGHTTOLERANCE)
        {
            inOrder = false;
        }
    }

    return inOrder;
}
