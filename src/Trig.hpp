#ifndef JE_TRIG_HPP
#define JE_TRIG_HPP

#include <SFML/System/Vector2.hpp>

namespace je
{

const float pi = 3.14159265;

extern float lengthdirX(float length, float dir);

extern float lengthdirY(float length, float dir);

extern sf::Vector2f lengthdir(float length, float dir);

extern float length(const sf::Vector2f& vec);


extern float pointDistance(const sf::Vector2f& a, const sf::Vector2f& b);

extern float pointDistance(float x1, float y1, float x2, float y2);


extern float pointDirection(const sf::Vector2f& a, const sf::Vector2f& b);

extern float pointDirection(const sf::Vector2f& vec);

extern float pointDirection(float x1, float y1, float x2, float y2);

}

#endif

