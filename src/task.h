#include <list>

#include "main.h"

#include "vector2.h"
#include "constants.h"
#include "helpers.h"
#include "devices.h"
#include "odometry.h"
#include "pid.h"

#ifndef TASK_H
#define TASK_H

class AutonTask
{
    public:
        double elapsedTime;
        
        virtual std::array<double, 2> getValue()
        {
            return {0.0, 0.0};
        }

        virtual bool checkComplete()
        {
            return false;
        }
};

class SetMotorSpeed : public AutonTask
{
    public:
        SetMotorSpeed(double _speed, double _maxTime)
        {
            speed = _speed;
            maxTime = _maxTime;
        }

        std::array<double, 2> getValue()
        {
            return {speed, speed};
        }

        bool checkComplete()
        {
            return elapsedTime > maxTime;
        }
    
    protected:
        double speed;
        double maxTime;
};

class FacePoint : public AutonTask
{
    public:
        FacePoint(Vector2 _point, double _errorThresh, double _maxPower = 0.2)
        {
            turnController = PIDController(0.5);

            errorThresh = _errorThresh;

            maxPower = _maxPower;

            point = _point;
        }

        std::array<double, 2> getValue()
        {
            double angError = Odometry::angle_to(point);

            double power = turnController.getAbsClampedValue(angError, maxPower);

            return {power, -power};
        }

        bool checkComplete()
        {
            double angError = Odometry::angle_to(point);

            return abs(angError) < errorThresh;
        }
    
    protected:
        PIDController turnController;
        
        Vector2 point;

        double errorThresh;
        double maxPower;
};

class MoveToPoint : public AutonTask
{
    public:
        MoveToPoint(Vector2 _point, double _errorThresh = 50, double _maxPower = 0.2)
        {
            maxAngleError = PI / 8.0;

            point = _point;

            maxPower = _maxPower;

            errorThresh = _errorThresh;

            moveController = PIDController(0.007);
            turnController = PIDController(1.0 / maxAngleError);
        }

        std::array<double, 2> getValue()
        {
            double linError = Odometry::distance_to(point);
            double angError = Odometry::angle_to(point);

            double absPower = moveController.getAbsClampedValue(linError, 1) * maxPower;

            double leftPower = absPower * turnController.getAbsClampedValue(maxAngleError + angError, 1);
            double rightPower = absPower * turnController.getAbsClampedValue(maxAngleError - angError, 1);

            return {leftPower, rightPower};
        }

        bool checkComplete()
        {
            double error = Odometry::distance_to(point);
            
            return error < errorThresh;
        }
    
    protected:
        Vector2 point;

        double errorThresh;
        
        double maxPower;

        PIDController moveController;
        PIDController turnController;

        double maxAngleError;
};

class MoveToPointXPlane : public MoveToPoint
{
    public:
        MoveToPointXPlane(Vector2 _point) : MoveToPoint(_point)
        {
            
        }

        std::array<double, 2> getValue()
        {
            return MoveToPoint::getValue();
        }

        bool checkComplete()
        {
            double error = abs(point.x - Odometry::x);
            
            return error < errorThresh;
        }
};

class MoveToPointYPlane : public MoveToPoint
{
    public:
        MoveToPointYPlane(Vector2 _point) : MoveToPoint(_point)
        {
            
        }

        std::array<double, 2> getValue()
        {
            return MoveToPoint::getValue();
        }

        bool checkComplete()
        {
            double error = abs(point.y - Odometry::y);
            
            return error < errorThresh;
        }
};

class SingleActionTask : public AutonTask
{
    public:
        void action()
        {

        }

        bool checkComplete()
        {
            action();

            return true;
        }
};

class ExpandFins : public SingleActionTask
{
    public:
        void action()
        {
            Controls::finsOut();
        }

        bool checkComplete()
        {
            return SingleActionTask::checkComplete();
        }
};

class RetractFins : public SingleActionTask
{
    public:
        void action()
        {
            Controls::finsIn();
        }

        bool checkComplete()
        {
            return SingleActionTask::checkComplete();
        }
};

#endif