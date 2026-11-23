#include "vex.h"

using namespace vex;

bool calibrateGantry() {

  // adjust later, placeholder values
  double rackPitchMmPerTurn = 40.0; // mm of rack travel per 1 motor turn 
  double gantryLengthMm = 400.0;
  double timeoutSeconds = 15.0;  // safety time limit per move
  color homeColor = red;  // optical color detected at home (0, 0), maybe detecting black would be better

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
  Optical3.setLight(ledState::on);
  safetyTimer.clear();
  xMotor.spin(reverse, 30, percent);

  // go back to home w/conditions 
  bool foundHome = false;
  while (!foundHome && 
        xMotor.position(turns)*xMotor.position(turns) < maxTurnsLimit*maxTurnsLimit && 
        safetyTimer.time(seconds) < timeoutSeconds) {
    
            if (Optical3.color() == homeColor) {
                foundHome = true;
            }
  }
  xMotor.stop(brake);
  Optical3.setLight(ledState::off);

  //  zero x and y
  xMotor.resetPosition();
  xMotor.setPosition(0, turns);
  yMotor.resetPosition();
  yMotor.setPosition(0, turns);

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