#include <stdio.h>
#include <math.h> 
#include <atomic>

#include "vector2.h" 
#include "helpers.h"
#include "constants.h"
#include "devices.h"
#include "odometry.h"
#include "smartscreen.h"
#include "pid.h"

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

class Controls
{
    public:
        Controls()
        {
            leftFinOut = false;
            rightFinOut = false;
        }

        //Sets the speed of the left side of the drivetrain
        static void setLeftSpeed(double power)
        {
            LeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            LeftMid.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            LeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

            int32_t int_power = power * 2.0 * 100.0;

            LeftFront.move(int_power);
            LeftMid.move(int_power);
            LeftBack.move(int_power);
        }

        //Sets the speed of the right side of the drivetrain
        static void setRightSpeed(double power)
        {
            RightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            RightMid.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
            RightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

            int32_t int_power = power * 2.0 * 100.0;

            RightFront.move(int_power);
            RightMid.move(int_power);
            RightBack.move(int_power);
        }

        //Sets left and right drivetrain speed
        static void setSpeed(double leftPower, double rightPower)
        {
            setLeftSpeed(leftPower);
            setRightSpeed(rightPower);
        }

        //Sets left and right speed to 0
        static void stop()
        {
            setSpeed(0.0, 0.0);
        }

        //Fin controls
        static bool leftFinOut;
        static bool rightFinOut;

        static void expandLeftFin()
        {
            leftFinOut = true;

            LeftFin.set_value(true);
        }

        static void retractLeftFin()
        {
            leftFinOut = false;

            LeftFin.set_value(false);
        }

        static void expandRightFin()
        {
            rightFinOut = true;

            RightFin.set_value(true);
        }

        static void retractRightFin()
        {
            rightFinOut = false;

            RightFin.set_value(false);
        }

        static void finsOut()
        {
            expandLeftFin();
            expandRightFin();
        }

        static void finsIn()
        {
            retractLeftFin();
            retractRightFin();
        }

        //Sets the speed of the catapult
        static void setCataSpeed(double value)
        {
            Catapult1.move_velocity(200.0 * value);
			Catapult2.move_velocity(200.0 * value);
        }
};

bool Controls::leftFinOut = false;
bool Controls::rightFinOut = false;

#endif