#include <list>

#include "main.h"

#include "vector2.h"
#include "constants.h"
#include "devices.h"
#include "odometry.h"
#include "vision.h"

#ifndef SMARTLOGGER_H
#define SMARTLOGGER_H

class SmartLogger
{
    public:
        static std::string filename;

        SmartLogger()
        {
            
        }

        static void startLog(std::string logFilename)
        {
            filename = logFilename;

            FILE* file = fopen(("/usd/" + filename).c_str(), "w");

            fclose(file);
        }

        static void writeToLog(std::string textToWrite)
        {
            FILE* file = fopen(("/usd/" + filename).c_str(), "w");

            fputs(textToWrite.c_str(), file);

            fclose(file);
        }
};

#endif