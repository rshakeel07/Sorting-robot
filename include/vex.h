#ifndef VEX_H_
#define VEX_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "iq2_cpp.h"

// ---------- Constants (placeholder values, tune during hardware testing) ----------
// all distances are in mm
#define CONVERSION_X 1 // motor turns per mm of x travel (rack and pinion)
#define CONVERSION_Y 1 // motor turns per mm of y travel (lead screw)
#define SPEED 1        // default motor speed (percent)
#define CLAWCLOSE 1    // how far to close the claw on a box (percent of max claw angle)
#define BOXWIDTH 1     // width of a box along the rail (mm), all boxes are the same width
#define XMAX 1         // max x length (mm)
#define YMAX 1         // max y height (mm)
#define ARRLENGTH 100  // max number of boxes in the box array
#define CLAWTIMEOUT 2  // max seconds the claw motor runs in one move before stopping
#define HOMEBRIGHTNESS 2 // optical brightness (%) at or below which the sensor counts as covered (carriage is home)

// scanning
#define SCANSPEED 1    // slow, constant x motor speed while scanning (percent)
#define SCANHEIGHT 1   // distance sensor reading (mm) with the claw at y = 0 and nothing underneath
#define BOXTHRESHOLD 1 // how much shorter (mm) the reading must be to count as a box (filters out noise)
#define BOXTIMEOUT 5   // max seconds a real box takes to pass under the sensor at SCANSPEED
#define BUFFER 10      // gap left on each side of a box when placing it (mm)
#define HEIGHTTOLERANCE 3 // heights this close (mm) count as equal when verifying, to allow for sensor jitter

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
bool boxdetect(double &minDistance);                            // Box.cpp
void nobox();                                                   // Box.cpp
bool scanend(bool forwardScan);                                 // DataCollection.cpp
int dataCollection(double boxes[ARRLENGTH][2], bool forwardScan, double &x_cur, double &y_cur); // DataCollection.cpp
double findspot(double startX, double &x_cur, double &y_cur);   // Sorting.cpp
bool sorting(double boxes[ARRLENGTH][2], int m, double &x_cur, double &y_cur); // Sorting.cpp
bool verifysort(int m, double &x_cur, double &y_cur);           // Verify.cpp
void shutdown(double &x_cur, double &y_cur);                    // Shutdown.cpp
bool calibrateGantry();                                         // Calibrate_Gantry.cpp
void claw(bool open, double speed, double percentage);          // Claw.cpp
void clawres();                                                 // Claw.cpp
void moveto(double x_tar, double y_tar, double &x_cur, double &y_cur, double speed); // Inversekin.cpp
void pickupandplace(double xbox, double ybox, double &x_cur, double &y_cur, double x_tar, double y_tar); // pickup.cpp

#endif
