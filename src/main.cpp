#include <stdio.h>
#include <math.h> 
#include <atomic>

#include "main.h"

#include "vector2.h" 
#include "constants.h"
#include "devices.h"
#include "helpers.h"
#include "smartscreen.h"
#include "odometry.h"
#include "controls.h"
#include "autons.h"
#include "vision.h"
#include "pid.h"

/**
 * Variable definitions
*/

bool initialized = false;

/**
 * PROS methods
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() 
{
	//Displaying initialization status on the brain
	pros::screen::erase();
	pros::screen::print(pros::E_TEXT_MEDIUM, 1, "Calibrating...");
	
	SmartScreen::initialize();

	Odometry::calibrate(false, Vector2(-1600, 1600), 3.0 * PI / 4.0);

	Controls::retractLeftFin();
	Controls::retractRightFin();

	//Vision::calibrate();

	//Displaying initialization status on the brain
	Controller1.clear();
	Controller1.print(0, 0, "Calibration complete");

	//Start up odometry
	pros::Task::create(Odometry::odometry, 16, 0x2000, "Odometry");

	//Start up field rendering
	pros::Task::create(SmartScreen::render, 16, 0x200, "Render");

	Controller1.print(1, 0, "Initialization complete");

	initialized = true;
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() 
{

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() 
{

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{

	while(!initialized)
		pros::delay(5);
	
	auton_skills();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *setSpeed(leftPower, rightPower);
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() 
{
	while (true) 
	{
		//Arcade drive
		double left_stick_x = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0;
		double left_stick_y = Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;

		Controls::setRightSpeed(left_stick_y - left_stick_x);
		Controls::setLeftSpeed(left_stick_x + left_stick_y);

		//Catapult controls
		if(Controller1.get_digital(DIGITAL_B))
			Controls::setCataSpeed(0.33);
		else if (Controller1.get_digital(DIGITAL_A))
			Controls::setCataSpeed(0.67);
		else if (Controller1.get_digital(DIGITAL_X))
			Controls::setCataSpeed(1.0);
		else 
			Controls::setCataSpeed(0.0);

		//Fin controls
		if (Controller1.get_digital_new_press(DIGITAL_L1))
		{
			if (Controls::leftFinOut)
				Controls::retractLeftFin();
			else
				Controls::expandLeftFin();
		}

		if (Controller1.get_digital_new_press(DIGITAL_R1))
		{
			if (Controls::rightFinOut)
				Controls::retractRightFin();
			else
				Controls::expandRightFin();
		}

	pros::delay(8); }
}