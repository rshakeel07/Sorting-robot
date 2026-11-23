#include "vex.h"

using namespace vex;

// Devices: the only globals allowed. Constants and function declarations are in include/vex.h.
// TODO: check that each port (and the true/false "reversed" setting on the motors) matches the robot.
brain Brain;
motor xMotor = motor(PORT1, false);
motor yMotor = motor(PORT2, false);
motor clawMotor = motor(PORT5, false);
optical Optical3 = optical(PORT3);
distance Distance4 = distance(PORT4);
bumper Bumper7 = bumper(PORT7);
touchled TouchLED9 = touchled(PORT9);

int main()
{
	// box data and current position are local and get passed into functions
	double boxes[ARRLENGTH][2];
	fillarray(boxes);
	double x_cur = 0;
	double y_cur = 0;

	// TODO: program flow (calibrateGantry, dataCollection, sorting, verification, shutdown)
}
