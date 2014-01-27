#ifndef JE_CAMERA_HPP
#define JE_CAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace je
{

class Level;

class Camera
{
public:
	Camera(Level *level, float maxSpeed, float acceleration);
	~Camera();

	void update(const sf::Vector2f& target);

	void snap(const sf::Vector2f& target);

	sf::View& getView();

private:
	Level *level;
	sf::View view;
	sf::Vector2f pos;
	sf::Vector2f veloc;
	float maxSpeed;
	float acceleration;
};

}

#endif
