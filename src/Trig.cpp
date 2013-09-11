#include "Trig.hpp"

#include <cmath>

namespace je
{

float lengthdirX(float length, float dir)
{
    return length * cos(dir / 180 * pi);
}

float lengthdirY(float length, float dir)
{
    return -length * sin(dir / 180 * pi);
}

sf::Vector2f lengthdir(float length, float dir)
{
    return sf::Vector2f(lengthdirX(length, dir), lengthdirY(length, dir));
}

float length(const sf::Vector2f& vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

float pointDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float pointDistance(float x1, float y1, float x2, float y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

float pointDirection(const sf::Vector2f& vec)
{
	return pointDirection(0, 0, vec.x, vec.y);
}

float pointDirection(const sf::Vector2f& a, const sf::Vector2f& b)
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

float pointDirection(float x1, float y1, float x2, float y2)
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


}

