#include "vector2.h"

#ifndef HELPERS_H
#define HELPERS_H

//Calculates the angle between two angles
double angleBetween(double angle1, double angle2)
{
	//Convert the angles to radians
	angle1 = angle1;
	angle2 = angle2;

	//Convert the angles into vectors
	Vector2 vec1(cos(angle1), sin(angle1));
	Vector2 vec2(cos(angle2), sin(angle2));

	//Calculate the dot product and determinant of the vectors
	double dot = vec1.x * vec2.x + vec1.y * vec2.y;
	double det = vec1.x * vec2.y - vec1.y * vec2.x;

	//Calculate the angle between the vectors
	double angle = atan2(det, dot);

	//Convert the angle back to degrees
	return angle;
}

//Calculates the angle between two vectors
double angleBetween(Vector2 vec1, Vector2 vec2)
{
	vec1 = vec1.normalize();
	vec2 = vec2.normalize();

	//Calculate the dot product and determinant of the vectors
	double dot = vec1.x * vec2.x + vec1.y * vec2.y;
	double det = vec1.x * vec2.y - vec1.y * vec2.x;

	//Calculate the angle between the vectors
	double angle = atan2(det, dot);

	//Convert the angle back to degrees
	return angle;
}

double clamp(double value, double min, double max)
{
	if (value > max) return max;
    else if (value < min) return min;
	else return value;
}

double absclamp(double value, double radius)
{
	return clamp(value, -radius, radius);
}

//algorithm referenced from https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/

//def ccw(A,B,C):
//	return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x)

bool ccw(Vector2 A, Vector2 B, Vector2 C)
{
	return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}

//def intersect(A,B,C,D):
//	return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D)

bool vectors_intersect(Vector2 start_one, Vector2 end_one, Vector2 start_two, Vector2 end_two)
{
	return (ccw(start_one, start_two, end_two) != ccw(end_one, start_two, end_two)) && (ccw(start_one, start_two, end_one) != ccw(start_one, end_one, end_two));
}

#endif