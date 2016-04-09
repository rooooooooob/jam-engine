#ifndef JE_TRIG_HPP
#define JE_TRIG_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace je
{

const float pi = 3.14159265;

/**
 * Calculates the x-component of a given magnitude/angle vector
 * @param length The magnitude of the vector
 * @param dir The angle of the vector in degrees going counter-clockwise and the positive x-axis at 0
 * @return the x-component
 */
inline float lengthdirX(float length, float dir)
{
	return length * cos(dir / 180 * pi);
}

/**
 * Calculates the y-component of a given magnitude/angle vector
 * @param length The magnitude of the vector
 * @param dir The angle of the vector in degrees going counter-clockwise and the positive x-axis at 0
 * @return the y-component
 */
inline float lengthdirY(float length, float dir)
{
	return -length * sin(dir / 180 * pi);
}

/**
 * Calculates the (x,y)-components of a given magnitude/angle vector
 * @param length The magnitude of the vector
 * @param dir The angle of the vector in degrees going counter-clockwise and the positive x-axis at 0
 * @return the the (x,y)-components as a vector
 */
inline sf::Vector2f lengthdir(float length, float dir)
{
	return sf::Vector2f(lengthdirX(length, dir), lengthdirY(length, dir));
}

/**
 * Calculates the (x,y)-components of a given magnitude/angle vector, but as an integer vector
 * @param length The magnitude of the vector
 * @param dir The angle of the vector in degrees going counter-clockwise and the positive x-axis at 0
 * @return the the (x,y)-components as a vector
 */
inline sf::Vector2i lengthdirI(float length, float dir)
{
	return sf::Vector2i(lengthdirX(length, dir), lengthdirY(length, dir));
}

/**
 * @param vec Input vector
 * @return The magnitude of the input vector
 */
template <typename VecType>
inline float length(const VecType& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

/**
 * Calculates the distance between two points
 * @param a First point
 * @param b Second point
 * @return distance between a and b
 */
template <typename VecTypeA, typename VecTypeB>
inline float pointDistance(const VecTypeA& a, const VecTypeB& b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/**
 * Calculates the distance between two points
 * @param x1 x-position of 1st point
 * @param y1 y-position of 1st point
 * @param x2 x-position of the 2nd point
 * @param y2 y-position of the 2nd point
 * @return distance between a and b
 */
inline float pointDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

/**
 * Calculates the angle from point a to point b
 * @param a Starting point
 * @param b Ending point
 * @return direction from a to b in degrees going counter-clockwise and the positive x-axis at 0
 */
template <typename VecTypeA, typename VecTypeB>
inline float pointDirection(const VecTypeA& a, const VecTypeB& b)
{
	float angle;
	if (b.x - a.x == 0)
	{
		if (b.y - a.y < 0)
			angle = 90;
		else
			angle = 270;
	}
	else
		angle = 180 / pi * atan((a.y - b.y) / (b.x - a.x));

	if (b.x - a.x < 0)
		angle += 180;
	else if (b.x - a.x > 0 && b.y - a.y > 0)
		angle += 360;
	return angle;
}

/**
 * Calculates the angle from point (x1,y1) to point (x2,y2)
 * @param x1 x-position of 1st point
 * @param y1 y-position of 1st point
 * @param x2 x-position of the 2nd point
 * @param y2 y-position of the 2nd point
 * @return direction from (x1,y1) to (x2,y2) in degrees going counter-clockwise and the positive x-axis at 0
 */
inline float pointDirection(float x1, float y1, float x2, float y2)
{
	float angle;
	if (x2 - x1 == 0)
	{
		if (y2 - y1 < 0)
			angle = 90;
		else
			angle = 270;
	}
	else
		angle = 180 / pi * atan((y1 - y2) / (x2 - x1));

	if (x2 - x1 < 0)
		angle += 180;
	else if (x2 - x1 > 0 && y2 - y1 > 0)
		angle += 360;
	return angle;
}

/**
 * @param vec A vector
 * @return vec's angle in degrees going counter-clockwise and the positive x-axis at 0
 */
template <typename VecType>
inline float direction(const VecType& vec)
{
	return pointDirection(0, 0, vec.x, vec.y);
}

}

#endif

