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
	int m = 0; // number of boxes found

	// 1. start-up: wait for the Touch LED to be pressed
	Brain.Screen.clearScreen();
	Brain.Screen.setCursor(1, 1);
	Brain.Screen.print("Press to start");
	while (!TouchLED9.pressing())
	{}

	if (calibrateGantry()) // prints its own messages and sets the Touch LED colour
	{
		x_cur = 0;
		y_cur = 0;

		// 2. initial scan from home to the bumper
		Brain.Screen.clearScreen();
		Brain.Screen.setCursor(1, 1);
		Brain.Screen.print("Scanning...");
		m = dataCollection(boxes, true, x_cur, y_cur);

		// 3. no boxes: wait, then scan back from the bumper to home in case boxes were placed
		if (m == 0)
		{
			Brain.Screen.clearScreen();
			Brain.Screen.setCursor(1, 1);
			Brain.Screen.print("No boxes, waiting...");
			nobox();

			Brain.Screen.clearScreen();
			Brain.Screen.setCursor(1, 1);
			Brain.Screen.print("Scanning again...");
			m = dataCollection(boxes, false, x_cur, y_cur);
		}

		if (m == 0)
		{
			TouchLED9.on(red);
			Brain.Screen.setCursor(2, 1);
			Brain.Screen.print("No boxes found");
		}
		else
		{
			// 4. sorting, starting from home
			Brain.Screen.clearScreen();
			Brain.Screen.setCursor(1, 1);
			Brain.Screen.print("Sorting...");
			moveto(0, 0, x_cur, y_cur, SPEED); // the claw is already at the top after scanning
			bool sorted = sorting(boxes, m, x_cur, y_cur);

			// 5. verification (skipped if sorting already failed)
			bool success = false;
			if (sorted)
			{
				Brain.Screen.clearScreen();
				Brain.Screen.setCursor(1, 1);
				Brain.Screen.print("Verifying...");
				success = verifysort(m, x_cur, y_cur);
			}

			Brain.Screen.setCursor(2, 1);
			if (success)
			{
				TouchLED9.on(green);
				Brain.Screen.print("Sorting Successful");
			}
			else
			{
				TouchLED9.on(orange);
				Brain.Screen.print("Sorting Failed");
			}
		}

		// 6. shutdown: raise the claw, go home, stop everything
		shutdown(x_cur, y_cur);
	}
	else
	{
		// calibration failed, so the robot doesn't know where it is: stop without moving
		xMotor.stop(brake);
		yMotor.stop(brake);
		clawMotor.stop(brake);
		Brain.programStop();
	}
}
