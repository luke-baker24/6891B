#include <list>

#include "main.h"

#include "vector2.h"
#include "constants.h"
#include "helpers.h"
#include "devices.h"
#include "odometry.h"

#ifndef VISION_H
#define VISION_H

class Vision
{
    public:
        static void calibrate()
        {
            //signature Vision14__G_TRIBALL = signature (1, -5857, -4085, -4971, -5739, -3807, -4773, 2.4, 0);
            pros::vision_signature_s_t TRIBALL = pros::Vision::signature_from_utility(G_TRIBALL, -5857, -4085, -4971, -5739, -3807, -4773, 2.4, 0);
            //pros::vision_signature_s_t BLUE_TRIBALL = pros::Vision::signature_from_utility(B_TRIBALL, -4497, -3933, -4215, 12531, 15157, 13844, 8.3, 0);
            //pros::vision_signature_s_t RED_TRIBALL = pros::Vision::signature_from_utility(R_TRIBALL, 7979, 9621, 8800, -2495, -1843, -2168, 6.5, 0);

            VisionSensor.set_signature(G_TRIBALL, &TRIBALL);
            //VisionSensor.set_signature(B_TRIBALL, &BLUE_TRIBALL);
            //VisionSensor.set_signature(R_TRIBALL, &RED_TRIBALL);
        }

        static std::list<pros::vision_object_s_t> getObjects()
        {
            int objectCount = VisionSensor.get_object_count();

            std::list<pros::vision_object_s_t> objects;

            for (int i = 0; i < objectCount; i++)
            {
                objects.push_back(VisionSensor.get_by_size(i));
            }

            return objects;
        }

        static std::list<pros::vision_object_s_t> filterObjects()
        {
            std::list<pros::vision_object_s_t> objects = getObjects();

            std::list<pros::vision_object_s_t> filteredObjects;

            for (int i = 0; i < objects.size(); i++)
            {
                pros::vision_object_s_t currentObject = objects.front();

                bool validObject = true;


                Vector2 robot_pos = Odometry::get_position();
                Vector2 heading_vector_extended = robot_pos.add(Odometry::get_heading_vector().mult(5100));

                if (vectors_intersect(robot_pos, heading_vector_extended, Vector2(1800.0, 600.0), Vector2(1200.0, 600.0)))
                {

                }

                if(validObject)
                {
                    filteredObjects.push_front(currentObject);
                }

                objects.pop_front();
            }
        }
};

#endif