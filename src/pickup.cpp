#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// define your global instances of motors and other devices here

#define CONVERSION_X 1 // arbitrary value for conversion factor of distance to motor turns
#define CONVERSION_Y 1 // same but for y
#define MOTORSPEED 1 // arbitrary motor speed percentage

void pickup(int height, )

// goes to pos of box in x
// lowers down to height
