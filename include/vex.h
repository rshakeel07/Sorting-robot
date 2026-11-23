#ifndef VEX_H_
#define VEX_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "iq2_cpp.h"

// ---------- Constants (placeholder values, tune during hardware testing) ----------
#define CONVERSION_X 1 // motor turns per unit of x distance (rack and pinion)
#define CONVERSION_Y 1 // motor turns per unit of y distance (lead screw)
#define SPEED 1        // default motor speed (percent)
#define BOXWIDTH 1     // how far to close the claw on a box (percent of max claw angle)
#define XMAX 1         // max x length
#define YMAX 1         // max y height
#define ARRLENGTH 100  // max number of boxes in the box array
#define CLAWTIMEOUT 2  // max seconds the claw motor runs in one move before stopping

// ---------- Devices (the only globals; defined once in main.cpp) ----------
extern vex::brain Brain;
extern vex::motor xMotor;
extern vex::motor yMotor;
extern vex::motor clawMotor;
extern vex::optical Optical3;
extern vex::distance Distance4;
extern vex::bumper Bumper7;
extern vex::touchled TouchLED9;

// ---------- Functions (so every file can call them) ----------
void fillarray(double arr[ARRLENGTH][2]);                       // Arrayfill.cpp
bool boxdetect();                                               // Box.cpp
void nobox();                                                   // Box.cpp
bool calibrateGantry();                                         // Calibrate_Gantry.cpp
void claw(bool open, double speed, double percentage);          // Claw.cpp
void clawres();                                                 // Claw.cpp
void moveto(double x_tar, double y_tar, double &x_cur, double &y_cur, double speed); // Inversekin.cpp
void pickupandplace(double xbox, double ybox, double &x_cur, double &y_cur, double x_tar, double y_tar); // pickup.cpp

#endif
