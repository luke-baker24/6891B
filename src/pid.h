#include "main.h"

#include "vector2.h"
#include "constants.h"
#include "helpers.h"
#include "devices.h"

#ifndef PID_H
#define PID_H

class PIDController
{
    public:
        PIDController(double _kP = 0.0, double _kI = 0.0, double _kD = 0.0)
        {
            kP = _kP;
            kI = _kI;
            kD = _kD;

            firstUpdate = true;
        }

        double getValue(double error)
        {
            double deltaError;

            if (firstUpdate)
            {
                deltaError = 0.0;
                firstUpdate = false;
            }
            else
                deltaError = error - oldError;

            integral += error;

            oldError = error;

            return kP * error + kI * integral + kD * deltaError;
        }

        double getClampedValue(double error, double min, double max)
        {
            return clamp(getValue(error), min, max);
        }

        double getAbsClampedValue(double error, double radius)
        {
            return getClampedValue(error, -radius, radius);
        }
    
    private:
        double kP;
        double kI;
        double kD;

        double oldError;

        double integral;

        bool firstUpdate;
};

#endif