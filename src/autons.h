#include <stdio.h>
#include <math.h> 
#include <atomic>

#include "main.h"

#include "vector2.h" 
#include "constants.h"
#include "devices.h"
#include "controls.h"
#include "task.h"

#ifndef AUTONS_H
#define AUTONS_H

//Left side autonomous routine
void left_side_auton()
{
    //Fire the alliance preload triball
    //Catapult.move_relative(180.0, 50.0);
}

//Right side autonomous routine
void right_side_auton()
{

}

//Autonomous skills routine
void auton_skills()
{
    //Fire 44 match loads
	/*while ((Catapult1.get_position() + Catapult2.get_position()) / 2.0 < 360.0 * 44.0)
	{
		Controls::setCataSpeed(1);
	}*/

	//Sweeps
	std::list<AutonTask*> tasks;

	//go under elevation bar
	tasks.push_back(new MoveToPointXPlane(Vector2(0.0, 1500.0)));
	tasks.push_back(new MoveToPointXPlane(Vector2(900.0, 1500.0)));

	//first sweep
	tasks.push_back(new MoveToPointXPlane(Vector2(1000.0, 1300.0)));
	tasks.push_back(new MoveToPointYPlane(Vector2(1500.0, 600.0)));
	tasks.push_back(new SetMotorSpeed(-0.5, 0.5));

	//second sweep
	tasks.push_back(new FacePoint(Vector2(300, 900), PI / 72.0));
	tasks.push_back(new MoveToPointXPlane(Vector2(300, 900)));

	//tasks.push_back(new ExpandFins());

	tasks.push_back(new MoveToPointXPlane(Vector2(1200, 100)));

	//tasks.push_back(new RetractFins());

	//third sweep
	tasks.push_back(new SetMotorSpeed(-0.5, 0.5));
	tasks.push_back(new FacePoint(Vector2(300, 0), PI / 72.0));
	tasks.push_back(new MoveToPointXPlane(Vector2(300, 0)));
	tasks.push_back(new MoveToPointYPlane(Vector2(300, -600)));
		
	//tasks.push_back(new ExpandFins());

	tasks.push_back(new MoveToPointXPlane(Vector2(1200, 100)));

	//tasks.push_back(new RetractFins());

	tasks.push_back(new SetMotorSpeed(-0.5, 0.5));

	//fourth sweep ..? 

	const int delayInterval = 8;

	for (auto current = tasks.begin(); current != tasks.end(); ++current)
	{
		// Move to next task
		while (!(*current)->checkComplete()) // Dereference the pointer and then call the function
		{
			// Get power from current task
			std::array<double, 2> drivePower = (*current)->getValue(); // Dereference and call getValue

			double leftPower = drivePower[0];
			double rightPower = drivePower[1];

			Controls::setSpeed(leftPower, rightPower);

			(*current)->elapsedTime += delayInterval;

			pros::delay(delayInterval);
		}

		delete *current;
	}

	//Score as many triballs as possible with fins
}

/*
void auton_tester()
{
    face_point(Vector2(-900.0, 1500.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(-900.0, 1500.0)));

	face_point(Vector2(900.0, 1500.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(900.0, 1500.0)));

	face_point(Vector2(900.0, 900.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(900.0, 900.0)));

	face_point(Vector2(600.0, 0.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(600.0, 0.0)));

	face_point(Vector2(-1200.0, 0.0));

	face_point(Vector2(900.0, -900.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(900.0, -900.0)));

	face_point(Vector2(900.0, -1500.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(900.0, -1500.0)));

	face_point(Vector2(-900.0, -1500.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(-900.0, -1500.0)));

	face_point(Vector2(0.0, -1500.0));
	move_mm(Vector2::distance(Vector2(x, y), Vector2(0.0, -1500.0)));
}
*/

/*
void triball_vision_test()
{
	while (true) 
	{
		if (VisionSensor.get_object_count() == 0) 
		{
			Drivetrain::setLeftSpeed(0.0);
			Drivetrain::setRightSpeed(0.0);

			continue;
		}

		pros::vision_object_s_t largest = VisionSensor.get_by_sig(0, 1);

		//316 by 212

		if(largest.x_middle_coord < -40)
		{
			Drivetrain::setLeftSpeed(-0.2);
			Drivetrain::setRightSpeed(0.2);
		}
		else if (largest.x_middle_coord > 40)
		{
			Drivetrain::setLeftSpeed(0.2);
			Drivetrain::setRightSpeed(-0.2);
		}
		else
		{
			if (largest.width > 300)
			{
				Drivetrain::setLeftSpeed(0);
				Drivetrain::setRightSpeed(0);

				Intake.move_velocity(-200.0);

				break;
			}
			else if (largest.width > 200)
			{
				Drivetrain::setLeftSpeed(0.2);
				Drivetrain::setRightSpeed(0.2);

				Intake.move_velocity(-200.0);
			}
			else
			{
				Drivetrain::setLeftSpeed(0.2);
				Drivetrain::setRightSpeed(0.2);
			}
		}

	pros::delay(8); }

	Drivetrain::face_point(Vector2(0.0, 0.0));

	Drivetrain::move_to_point(Vector2(0.0, 0.0));

	Drivetrain::face_point(Vector2(-1000.0, 0.0));

	Intake.move_velocity(200.0);

	pros::delay(3000);

	Intake.move_velocity(0.0);

	Drivetrain::face_point(Vector2(0.0, 1000.0));
}
*/

#endif