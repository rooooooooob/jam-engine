#include "jam-engine/Physics/CircleMask.hpp"

#include "jam-engine/Physics/PolygonMask.hpp"
#include "jam-engine/Physics/CollisionCheckingImplementation.hpp"
#include "jam-engine/Utility/Assert.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace je
{

CircleMask::CircleMask(float radius)
	:DetailedMask(Type::Circle)
	,center(0.f, 0.f)
	,radius(radius)
	,originalRadius(radius)
#ifdef JE_DEBUG
	,debugCircle(radius)
#endif
{
	JE_ASSERT(radius >= 0.f);
#ifdef JE_DEBUG
	debugCircle.setFillColor(sf::Color(0, 128, 256, 64));
	debugCircle.setOutlineColor(sf::Color::Cyan);
	debugCircle.setOutlineThickness(1.f);
#endif
}

const sf::Transformable& CircleMask::getBaseTransform() const
{
	return baseTransform;
}

sf::Transformable& CircleMask::getBaseTransform()
{
	return baseTransform;
}

float CircleMask::getRadius() const
{
	return radius;
}

const sf::Vector2f& CircleMask::getPos() const
{
	return center;
}

void CircleMask::projectAgainstHyerplane(double& min, double& max, double angle) const
{
	const double sinAngle = sin(-angle * pi / 180.f);
	const double cosAngle = cos(-angle * pi / 180.f);
	min = max = cosAngle * center.x + sinAngle * center.y;
	min -= radius;
	max += radius;
}

bool CircleMask::intersects(const DetailedMask& other) const
{
	switch (other.type)
	{
		case Type::Polygon:
			return intersectsPolygonOnCircle(static_cast<const PolygonMask&>(other), *this);
		case Type::Circle:
			return intersectsCircleOnCircle(*this, static_cast<const CircleMask&>(other));
		case Type::Pixel:
			return true;
	}
	return false;
}

void CircleMask::getAABB(int& minX, int& maxX, int& minY, int& maxY) const
{
	minX = center.x - radius;
	maxX = center.x + radius;
	minY = center.y - radius;
	maxY = center.y + radius;
}

void CircleMask::updateTransform(const sf::Transform& transform)
{
	const sf::Vector2f x1(transform.transformPoint(-1.f, 0.f));
	const sf::Vector2f x2(transform.transformPoint(1.f, 0.f));
	const sf::Vector2f y1(transform.transformPoint(0.f, -1.f));
	const sf::Vector2f y2(transform.transformPoint(0.f, 1.f));

	const float scaleX = je::length(x2 - x1);
	const float scaleY = je::length(y2 - y1);

	// until we decide to handle elipses
	const float epsilon = 0.1f;
	JE_ASSERT(scaleX >= scaleY - epsilon && scaleX <= scaleY + epsilon);

	radius = originalRadius * scaleX * baseTransform.getScale().x;
	center = baseTransform.getTransform().transformPoint((x2 + x1) * 0.5f);

#ifdef JE_DEBUG
	debugCircle.setRadius(radius);
	debugCircle.setOrigin(radius, radius);
	debugCircle.setPosition(center);
#endif
}

DetailedMask::MaskRef CircleMask::clone() const
{
	return DetailedMask::MaskRef(new CircleMask(*this));
}

#ifdef JE_DEBUG
void CircleMask::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(debugCircle, states);
}

void CircleMask::setColor(sf::Color color)
{
	debugCircle.setOutlineColor(color);
}
#endif


} // je
