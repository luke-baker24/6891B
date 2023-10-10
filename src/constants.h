#include "vector2.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H


//Math values
const double PI = 3.141593;
const double TWOPI = PI * 2.0;
const double PI_OVER_TWO = PI / 2.0; 


//Odometry constant
const double tracking_wheel_diameter = 69.85; //in mm
const double drivetrain_wheel_diameter = 101.6; //in mm
const double drivetrain_width = 292.1; //in mm


//Field reference points
//Note: Positive Y is standing at the red elevation bar facing the blue bar (blue goal to left, red goal to right)
const Vector2 blueGoalpost1(-1200.0, 600.0);
const Vector2 blueGoalpost2(-1200.0, -600.0);

const Vector2 redGoalpost1(1200.0, 600.0);
const Vector2 redGoalpost2(1200.0, -600.0);

const Vector2 redElevationPost(0, -1200.0);
const Vector2 blueElevationPost(0, 1200.0);


//Motor ports
#define LEFT_FRONT_PORT 1
#define LEFT_MID_PORT 2
#define LEFT_BACK_PORT 3

#define RIGHT_FRONT_PORT 10
#define RIGHT_MID_PORT 9
#define RIGHT_BACK_PORT 8

#define CATA_1_PORT 7
#define CATA_2_PORT 5

//Sensor ports
#define INERTIAL_PORT 21
#define GPS_PORT 14
#define VISION_PORT 15

//Odometry ports
//#define LEFT_ROTATION_PORT 14
//#define RIGHT_ROTATION_PORT 19
#define CENTER_ROTATION_PORT 18

//Vision configs
#define G_TRIBALL 1
#define B_TRIBALL 2
#define R_TRIBALL 3

//Pneumatic ports
#define LEFT_FIN_PNEUMATIC_PORT 'A'
#define RIGHT_FIN_PNEUMATIC_PORT 'B'

#endif