#include "vex.h"

using namespace vex;

// sets every entry in the box array to 0
void fillarray(double arr[ARRLENGTH][2])
{
    for (int i = 0; i < ARRLENGTH; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            arr[i][j] = 0.0;
        }
    }
}
