#include "main.h"

#include "vector2.h"
#include "constants.h"
#include "helpers.h"
#include "devices.h"

#ifndef ODOMETRY_H
#define ODOMETRY_H

class Odometry
{
    public:
        static double x;
        static double y;

        static double heading;

        static int totalTime;

        //Get the current position from odometry
        static Vector2 get_position()
        {
            return Vector2(x, y);
        }

        //Get the current heading as a vector
        static Vector2 get_heading_vector()
        {
            return Vector2(sin(heading), cos(heading));
        }

        //Get the angle between the current position and another point
        static double angle_to(Vector2 point)
        {
            Vector2 to_point = vector_to(point);

            return angleBetween(to_point, get_heading_vector());
        }

        //Get the distance to another point
        static double distance_to(Vector2 point)
        {
            return Vector2::distance(point, get_position());
        }

        //Get the vector between one point to another
        static Vector2 vector_to(Vector2 point)
        {
            return Vector2(point.x - x, point.y - y);
        }

        static double getInertialReading()
        {
            double raw_value = Inertial.get_rotation() * TWOPI / 360.0;

            double rounded_value = std::ceil(raw_value * 100.0) / 100.0;

            return rounded_value;
        }
        
        static double calculateDTheta(double dL, double dR)
        {
            return (dL - dR) / (drivetrain_width);
        }

        static double getLeftRotation()
        {
            //return LeftRotation.get_position() * (tracking_wheel_diameter * PI) / (36000.0);

            int motorsActive = 0;

            double leftFrontMotorValue, leftMidMotorValue, leftBackMotorValue = 0.0;

            if (LeftFront.get_current_draw() > 0)
            {
                leftFrontMotorValue = LeftFront.get_position();
                motorsActive++;
            }

            if (LeftMid.get_current_draw() > 0)
            {
                leftMidMotorValue = LeftMid.get_position();
                motorsActive++;
            }

            if (LeftBack.get_current_draw() > 0)
            {
                leftBackMotorValue = LeftBack.get_position();
                motorsActive++;
            }


            if(motorsActive == 0) return 0;

            return ((leftFrontMotorValue + leftMidMotorValue + leftBackMotorValue) / motorsActive) * (drivetrain_wheel_diameter * PI) / (360.0);
        }

        static double getRightRotation()
        {
            //return RightRotation.get_position() * (tracking_wheel_diameter * PI) / (36000.0);

            int motorsActive = 0;

            double rightFrontMotorValue, rightMidMotorValue, rightBackMotorValue = 0.0;

            if (RightFront.get_current_draw() > 0)
            {
                rightFrontMotorValue = RightFront.get_position();
                motorsActive++;
            }

            if (RightMid.get_current_draw() > 0)
            {
                rightMidMotorValue = RightMid.get_position();
                motorsActive++;
            }

            if (RightBack.get_current_draw() > 0)
            {
                rightBackMotorValue = RightBack.get_position();
                motorsActive++;
            }

            if(motorsActive == 0) return 0;

            return -((rightFrontMotorValue + rightMidMotorValue + rightBackMotorValue) / motorsActive) * (drivetrain_wheel_diameter * PI) / (360.0);
        }

        static double getCenterRotation()
        {
            return CenterRotation.get_position() * (tracking_wheel_diameter * PI) / (36000.0);
        }

        //Uses 3 odometers to perform odometry calculations
        static void odometry()
        {
            const int delayInterval = 8; //measured in milliseconds

            //Initializing old sensor values
            double leftEncoderOld = getLeftRotation();
            double rightEncoderOld = getRightRotation();
            double centerEncoderOld = getCenterRotation();

            double headingOld = heading;

            while (true)
            {
                //Getting new sensor values from odometers
                double leftEncoder = getLeftRotation();
                double rightEncoder = getRightRotation();
                double centerEncoder = getCenterRotation();

                //Calculating difference in sensor values
                double dL = (leftEncoder - leftEncoderOld);       //in mm
                double dR = (rightEncoder - rightEncoderOld);     //in mm
                double dB = (centerEncoder - centerEncoderOld);   //in mm

                //Updating the heading
                heading += calculateDTheta(dL, dR);

                double dTheta = angleBetween(heading, headingOld);

                //We regard the side encoder just as one of the wheels
                double dS = (dL - dR) / 2.0;

                //This case is rare but if it happens then the odometry math will not work
                if(dTheta == 0.0)
                {
                    x = x + dB * cos(heading) - dS * sin(heading);
                    y = y + dB * sin(heading) + dS * cos(heading);
                }

                //This is the most common case
                else
                {
                    double movementVecAngle = headingOld + (dTheta / 2.0);

                    double deltaDSide = 2.0 * dS * sin(dTheta / 2.0) / dTheta;

                    x = x + sin(movementVecAngle) * deltaDSide;
                    y = y + cos(movementVecAngle) * deltaDSide;

                    double deltaDBack = 2.0 * dB * sin(dTheta / 2.0) / dTheta;

                    x = x - cos(movementVecAngle) * deltaDBack;
                    y = y + sin(movementVecAngle) * deltaDBack;
                }

                //Updating old sensor values
                leftEncoderOld = leftEncoder;
                rightEncoderOld = rightEncoder;
                centerEncoderOld = centerEncoder;

                headingOld = heading;

                //Incrementing the total time value
                totalTime += delayInterval;

            pros::delay(delayInterval); }
        }

        //Sets the robot's position based on the GPS
        static void init_gps_position()
        {
            pros::c::gps_status_s_t gpsData;

            //Returns GPS position in meters
            gpsData = GPS.get_status();

            while (gpsData.x == 0.0 || gpsData.y == 0.0 || gpsData.yaw == 0.0)
            {
                gpsData = GPS.get_status();

                pros::delay(8);
            }

            x = gpsData.x * 1000.0;
            y = gpsData.y * 1000.0;

            //Get gps heading
            heading = gpsData.yaw * (PI / 180.0) + PI_OVER_TWO;

            Inertial.set_rotation(heading * (180.0 / PI));
        }

        //Calibrate the odometry system
        static void calibrate(bool use_gps_position, Vector2 start_pos = Vector2(0.0, 0.0), double start_heading = 0.0)
        {
            Inertial.reset();

            while (Inertial.is_calibrating()) pros::delay(5);

            //Resetting the inertial
            Inertial.tare_yaw();
            Inertial.tare_roll();
            Inertial.tare_pitch();

            LeftFront.tare_position();
            LeftMid.tare_position();
            LeftBack.tare_position();

            RightFront.tare_position();
            RightMid.tare_position();
            RightBack.tare_position();

            //Resetting the values of odometers
            //LeftRotation.reset_position();
            //RightRotation.reset_position();
            CenterRotation.reset_position();
            
            //These values will change based on the beginning of the autonomous period
            if(use_gps_position)
            {
                init_gps_position();
            }
            else
            {
                x = start_pos.x;
                y = start_pos.y;

                Inertial.set_rotation(start_heading * 360.0 / TWOPI);

                heading = start_heading;
            }
        }
};

double Odometry::x = 0.0;
double Odometry::y = 0.0;
double Odometry::heading = 0.0;

int Odometry::totalTime = 0;

#endif