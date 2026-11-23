#include "vex.h"

using namespace vex;

bool calibrateGantry() {

  // adjust later, placeholder values
  double rackPitchMmPerTurn = 40.0; // mm of rack travel per 1 motor turn 
  double gantryLengthMm = 400.0;
  double timeoutSeconds = 15.0;  // safety time limit per move
  // the claw must be raised to the top (y = 0) by hand before starting, since there is no sensor at the top of the y axis

  TouchLED9.on(yellow);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("Calibrating...");

  // move horizontally along the rack and pinion until the end bumper is pressed
  timer safetyTimer;
  safetyTimer.clear();
  xMotor.spin(forward, 30, percent);

  while (!Bumper7.pressing() && safetyTimer.time(seconds) < timeoutSeconds) {

  }
  xMotor.stop(brake);

  if (!Bumper7.pressing()) {
    TouchLED9.on(red);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Bumper not reached");
    return false;
  }

  // zero encoder at bumper and calculate the expected travel turns from end-to-end
  xMotor.resetPosition();
  double maxTurnsExpected = gantryLengthMm / rackPitchMmPerTurn;
  double maxTurnsLimit = maxTurnsExpected * 1.15; // allowing for small uncertainty margin

  // return along the rack and pinion to (0, 0) position
  // light stays off so the sensor reads dark (brightness near 0) when the carriage covers it at home
  // (with the light on, it would see its own light reflecting off the carriage and read bright)
  Optical3.setLight(ledState::off);
  safetyTimer.clear();
  xMotor.spin(reverse, 30, percent);

  // go back to home w/conditions 
  bool foundHome = false;
  while (!foundHome && 
        xMotor.position(turns)*xMotor.position(turns) < maxTurnsLimit*maxTurnsLimit && 
        safetyTimer.time(seconds) < timeoutSeconds) {
    
            if (Optical3.brightness() <= HOMEBRIGHTNESS) { // sensor is covered, so the carriage is home
                foundHome = true;
            }
  }
  xMotor.stop(brake);

  //  zero x and y (y = 0 is where the claw was set by hand)
  xMotor.resetPosition();
  xMotor.setPosition(0, turns);
  yMotor.resetPosition();
  yMotor.setPosition(0, turns);

  // open the claw fully and zero its position
  clawres();

  if (foundHome) {
    TouchLED9.on(green);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Home verified");
    return true;
  } else {
    TouchLED9.on(orange);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Home check failed");
    return false;
  }
}