#include <math.h>       /* sqrt */

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
    public:
        double x;
        double y;

        Vector2(double _x, double _y)
        {
            x = _x;
            y = _y;
        }

        Vector2(double len)
        {
            x = len;
            y = len;
        }

        Vector2()
        {
            x = 0;
            y = 0;
        }


        double lengthSquared()
        {
            return (x * x) + (y * y);
        }

        double length()
        {
            return sqrt((x * x) + (y * y));
        }

        Vector2 normalize()
        {
            return Vector2(x / length(), y / length());
        }

        Vector2 add(Vector2 vec2)
        {
            return Vector2(x + vec2.x, y + vec2.y);
        }

        Vector2 sub(Vector2 vec2)
        {
            return Vector2(x - vec2.x, y - vec2.y);
        }

        Vector2 mult(Vector2 vec2)
        {
            return Vector2(x * vec2.x, y * vec2.y);
        }

        double dot(Vector2 vec2)
        {
            return (x * vec2.x) + (y * vec2.y);
        }

        static double distance(Vector2 vec1, Vector2 vec2)
        {
            return sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y));
        }
};

class Vector4
{
    public:
        Vector2 vec1;
        Vector2 vec2;

        Vector4(double vec11, double vec12, double vec21, double vec22)
        {
            vec1 = Vector2(vec11, vec12);
            vec2 = Vector2(vec21, vec22);
        }
};

#endif