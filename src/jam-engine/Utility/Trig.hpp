#ifndef JE_TRIG_HPP
#define JE_TRIG_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace je
{

const float pi = 3.14159265;

inline float lengthdirX(float length, float dir)
{
	return length * cos(dir / 180 * pi);
}

inline float lengthdirY(float length, float dir)
{
	return -length * sin(dir / 180 * pi);
}

inline sf::Vector2f lengthdir(float length, float dir)
{
	return sf::Vector2f(lengthdirX(length, dir), lengthdirY(length, dir));
}

inline sf::Vector2i lengthdirI(float length, float dir)
{
	return sf::Vector2i(lengthdirX(length, dir), lengthdirY(length, dir));
}

template <typename VecType>
inline float length(const VecType& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

template <typename VecTypeA, typename VecTypeB>
inline float pointDistance(const VecTypeA& a, const VecTypeB& b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline float pointDistance(float x1, float y1, float x2, float y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

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

template <typename VecType>
inline float direction(const VecType& vec)
{
	return pointDirection(0, 0, vec.x, vec.y);
}

}

#endif

