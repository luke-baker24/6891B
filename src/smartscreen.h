#include <list>

#include "main.h"

#include "vector2.h"
#include "constants.h"
#include "devices.h"
#include "odometry.h"
#include "vision.h"

#ifndef SMARTSCREEN_H
#define SMARTSCREEN_H

class SmartScreen
{
    public:
        SmartScreen()
        {
            marker_x = 0.0;
            marker_y = 0.0;
            marker_heading = 0.0;
        }

        //Display variables
        static double marker_x;
        static double marker_y;
        static double marker_heading;

        static void draw_robot(auto color, double x, double y, double heading)
        {
            //Render bot
            pros::screen::set_pen(color);
            
            double field_x = 150 + 90 + (x * (180.0 / 3600.0));
            double field_y = 10 + 90 - (y * (180.0 / 3600.0));

            double forwardX = field_x + sin(heading) * 10;
            double forwardY = field_y - cos(heading) * 10;

            double backX = field_x + sin(heading + PI) * 5;
            double backY = field_y - cos(heading + PI) * 5;

            double leftX = field_x + sin(heading - PI_OVER_TWO * 1.5) * 10;
            double leftY = field_y - cos(heading - PI_OVER_TWO * 1.5) * 10;

            double rightX = field_x + sin(heading + PI_OVER_TWO * 1.5) * 10;
            double rightY = field_y - cos(heading + PI_OVER_TWO * 1.5) * 10;

            //Front 2 lines of the bot
            pros::screen::draw_line(forwardX, forwardY, leftX, leftY);
            pros::screen::draw_line(forwardX, forwardY, rightX, rightY);

            //Back 2 lines
            pros::screen::draw_line(backX, backY, leftX, leftY);
            pros::screen::draw_line(backX, backY, rightX, rightY);

            pros::screen::fill_circle(field_x, field_y, 2);
        }

        //Displays the robot relative to the field
        static void render_field_and_bot()
        {
            //Clear background
            pros::screen::erase();

            //Render field
            pros::screen::set_pen(COLOR_GRAY);
            pros::screen::fill_rect(150,10,180 + 150,180 + 10);

            //Draw auton lines
            pros::screen::draw_line(150, 10 + 90 - 3, 150 + 180, 10 + 90 - 3);
            pros::screen::draw_line(150, 10 + 90 + 3, 150 + 180, 10 + 90 + 3);

            pros::screen::draw_line(150, 10 + 90 + 30, 150 + 90, 10 + 90 + 30);

            pros::screen::draw_line(150 + 90, 10 + 90 - 30, 150 + 180, 10 + 90 - 30);

            //Drawing the blue field goal
            pros::screen::set_pen(COLOR_BLUE);
            pros::screen::fill_rect(150,10 + 60,150 + 30,10 + 60 + 60);

            //Drawing the blue elevation bar
            pros::screen::fill_rect(150 + 90 - 2,10,150 + 90 + 2,10 + 30);

            //Drawing the red field goal
            pros::screen::set_pen(COLOR_RED);
            pros::screen::fill_rect(150 + 150,10 + 60,150 + 150 + 30,10 + 60 + 60);

            //Drawing the red elevation bar
            pros::screen::fill_rect(150 + 90 - 2,10 + 150,150 + 90 + 2,10 + 180);

            //Rendering the black bars in the middle of the map
            pros::screen::set_pen(COLOR_BLACK);
            pros::screen::fill_rect(150 + 60,10 + 30 - 2,150 + 120,10 + 30 + 2);

            pros::screen::fill_circle(150 + 60,10 + 30, 2);
            pros::screen::fill_circle(150 + 120,10 + 30, 2);

            pros::screen::fill_rect(150 + 60,10 + 150 - 2,150 + 120,10 + 150 + 2);

            pros::screen::fill_circle(150 + 60,10 + 150, 2);
            pros::screen::fill_circle(150 + 120,10 + 150, 2);

            pros::screen::fill_rect(150 + 90 - 2,10 + 30,150 + 90 + 2,10 + 150);

            //Elevation bar caps
            pros::screen::set_pen(COLOR_YELLOW);

            pros::screen::fill_circle(150 + 90,10 + 30, 2);
            pros::screen::fill_circle(150 + 90,10 + 150, 2);


            //Rendering the GPS position of the bot
            pros::c::gps_status_s_t gpsData = GPS.get_status();

            double gpsx = gpsData.x * 1000.0;
            double gpsy = gpsData.y * 1000.0;

            //Get gps heading
            double gpsheading = gpsData.yaw * (PI / 180.0) + PI;

            //Render GPS bot
            draw_robot(COLOR_YELLOW, gpsx, gpsy, gpsheading);

            //Render odometry bot
            draw_robot(COLOR_RED, absclamp(1800, Odometry::x), absclamp(1800, Odometry::y), Odometry::heading);

            //Render marker bot
            //draw_robot(COLOR_GREEN, marker_x, marker_y, marker_heading);
        }

        static void render()
        {
            while(true)
            {
                //Rendering the robot on the field
                render_field_and_bot();

            pros::delay(40); }
        }

        /*
        static void on_left_button()
        {
            static bool leftPressed = false;
            leftPressed = !leftPressed;
            if (leftPressed)
                left_side_auton();
        }

        static void on_center_button()
        {
            static bool centerPressed = false;
            centerPressed = !centerPressed;
            if (centerPressed)
                right_side_auton();
        }

        static void on_right_button()
        {
            static bool rightPressed = false;
            rightPressed = !rightPressed;
            if (rightPressed)
                auton_skills();
        }
        */

        static void initialize()
        {
            //pros::lcd::initialize();

            //pros::lcd::register_btn0_cb(on_left_button);
            //pros::lcd::register_btn1_cb(on_center_button);
            //pros::lcd::register_btn2_cb(on_right_button);
        }

        static void place_marker(double x, double y, double heading)
        {
            marker_x = x;
            marker_y = y;
            
            marker_heading = heading;
        }
};

double SmartScreen::marker_x = 0.0;
double SmartScreen::marker_y = 0.0;
double SmartScreen::marker_heading = 0.0;

#endif