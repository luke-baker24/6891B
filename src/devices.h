#include "main.h"

#include "constants.h"

#ifndef DEVICES_H
#define DEVICES_H

//Initializing motors
pros::Motor LeftFront(LEFT_FRONT_PORT, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LeftMid(LEFT_MID_PORT, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor LeftBack(LEFT_BACK_PORT, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor RightFront(RIGHT_FRONT_PORT, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor RightMid(RIGHT_MID_PORT, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor RightBack(RIGHT_BACK_PORT, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor Catapult1(CATA_1_PORT, pros::E_MOTOR_GEAR_GREEN, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor Catapult2(CATA_2_PORT, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_DEGREES);

//Initializing controller
pros::Controller Controller1 (pros::E_CONTROLLER_MASTER); 

//Initializing sensors
pros::IMU Inertial (INERTIAL_PORT);

const double gps_offset_x = -0.07;
const double gps_offset_y = -0.012;

pros::GPS GPS (GPS_PORT, gps_offset_x, gps_offset_y); //two constructor values are the two gps offset distances - in meters

//constructor true/false is reverse boolean
//pros::Rotation LeftRotation(LEFT_ROTATION_PORT, false);
//pros::Rotation RightRotation(RIGHT_ROTATION_PORT, false);
pros::Rotation CenterRotation(CENTER_ROTATION_PORT, true);

//Vision sensor
pros::Vision VisionSensor(VISION_PORT, pros::E_VISION_ZERO_CENTER);

//Pneumatics
pros::ADIDigitalOut LeftFin (LEFT_FIN_PNEUMATIC_PORT);
pros::ADIDigitalOut RightFin (RIGHT_FIN_PNEUMATIC_PORT);

#endif