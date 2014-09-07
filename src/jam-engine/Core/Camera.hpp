#ifndef JE_CAMERA_HPP
#define JE_CAMERA_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

namespace je
{

class Level;

class Camera
{
public:
	Camera(Level *level, float maxSpeed, float acceleration, const sf::Rect<int>& bounds, int depth = 0);
	~Camera();

	void update(const sf::Vector2f& target);

	void snap(const sf::Vector2f& target);

	sf::View& getView(); // don't use this

	const sf::View& getView() const;

	int getDepth() const;

	sf::FloatRect getScreenRect() const;

	const sf::Vector2f& getPosition() const;

private:
	void limitBounds();

	Level *level;
	sf::Rect<int> cameraBounds;
	sf::View view;
	sf::Vector2f pos;
	sf::Vector2f veloc;
	float maxSpeed;
	float acceleration;
	int depth;
};

}

#endif
