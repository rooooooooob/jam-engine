#include "jam-engine/Core/Camera.hpp"

#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace je
{

Camera::Camera(Level *level, float maxSpeed, float acceleration)
	:level(level)
	,view()
	,pos(0, 0)
	,veloc(0, 0)
	,maxSpeed(maxSpeed)
	,acceleration(acceleration)
{
	level->registerCamera(this);
}

Camera::~Camera()
{
	level->unregisterCamera(this);
}

void Camera::update(const sf::Vector2f& target)
{

	view.move(pos);
}

void Camera::snap(const sf::Vector2f& target)
{
}

sf::View& Camera::getView()
{
	return view;
}

}
