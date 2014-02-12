#include "jam-engine/Core/PolygonMask.hpp"

#include "jam-engine/Core/CollisionCheckingImplementation.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace je
{

void PolygonMask::projectAgainstHyerplane(int& min, int& max, float angle) const
{
	//	if we rotate the points by -angle, then our projection against the hyperplane (angle)
	//	becomes projecting against the x-asis, which lets use just take the x value of the
	//	transformed vector instead of having to actually project the vector and since y is 0
	//	for the transformed vector (and we don't use it anyway), we don't even need to transform it!
	const float sinAngle = sin(angle);
	const float cosAngle = cos(angle);
	min = max = cosAngle * points.front().x + sinAngle * points.front().y;
	//	skip the first point since we already did that
	for (std::vector<sf::Vector2i>::const_iterator it = points.begin() + 1, end = points.end(); it != end; ++it)
	{
		const int projectionX = cosAngle * it->x + sinAngle * it->y;
		if (projectionX < min)
			min = projectionX;
		if (projectionX > max)
			max = projectionX;
	}
}

bool PolygonMask::intersects(const DetailedMask& other) const
{
	switch (other.type)
	{
		case Type::Polygon:
			return intersectsPolygonOnPolygon(*this, other);
		case Type::Circle:
			return true;
		case Type::Pixel:
			return true;
	}
	return false;
}

void PolygonMask::getAABB(int& minX, int& maxX, int& minY, int& maxY) const
{
	maxX = minX = points.front().x;
	maxY = minY = points.front().y;
	//	skip the first point since we already did that
	for (std::vector<sf::Vector2i>::const_iterator it = points.begin() + 1, end = points.end(); it != end; ++it)
	{
		if (it->x > maxX)
			maxX = it->x;
		else if (it->x < minX)
			minX = it->x;

		if (it->y > maxY)
			maxY = it->y;
		else if (it->y < minY)
			minY = it->y;
	}
}

}