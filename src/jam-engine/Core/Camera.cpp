#include "jam-engine/Core/Camera.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Utility/Math.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace je
{

Camera::Camera(Level *level, float maxSpeed, float acceleration, int depth)
	:level(level)
	,view()
	,pos(0, 0)
	,veloc(0, 0)
	,maxSpeed(maxSpeed)
	,acceleration(acceleration)
	,depth(depth)
{
	level->registerCamera(this);
	//	by default, make the view the size of the window
	view.setSize(sf::Vector2f(level->getGame().getWindow().getSize()));
	//	by default, make the view take up the window
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
}

Camera::~Camera()
{
	level->unregisterCamera(this);
}
//	TODO: make not shit
void Camera::update(const sf::Vector2f& target)
{
	const float dist = pointDistance(pos, target);
	//if (dist < 4.f)
	//{
	//	pos = target;
	//	veloc.x = 0.f;
	//	veloc.y = 0.f;
	//}
	//else
	{
		veloc += lengthdir(acceleration * (min(8.f, dist)) / 8.f, pointDirection(pos, target));
		float len = length(veloc);
		if (len > maxSpeed)
			veloc *= maxSpeed / len;
		pos += veloc;
	}
	this->limitBounds();
	view.setCenter(pos);
}

void Camera::snap(const sf::Vector2f& target)
{
	pos = target;
	this->limitBounds();
	view.setCenter(pos);
}

sf::View& Camera::getView()
{
	return view;
}

const sf::View& Camera::getView() const
{
	return view;
}

int Camera::getDepth() const
{
	return depth;
}

sf::Rect<int> Camera::getScreenRect() const
{
	return sf::Rect<int>();
}


/*		private			*/
void Camera::limitBounds()
{
	const float halfViewWidth = view.getSize().x / 2.f;
	limit(pos.x, halfViewWidth, level->getWidth() - halfViewWidth);
	const float halfViewHeight = view.getSize().y / 2.f;
	limit(pos.y, halfViewHeight, level->getHeight() - halfViewHeight);
}

}
