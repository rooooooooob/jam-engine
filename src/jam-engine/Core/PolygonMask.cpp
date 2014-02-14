#include "jam-engine/Core/PolygonMask.hpp"

#include "jam-engine/Core/CollisionCheckingImplementation.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace je
{

PolygonMask::PolygonMask(int width, int height)
	:DetailedMask(Type::Polygon)
	,points(4)
	,pointsOriginal(4)
#ifdef JE_DEBUG
	,debugDrawPoints(sf::PrimitiveType::LinesStrip, 4)
#endif
{
	points[0] = pointsOriginal[0] = sf::Vector2f(0, 0);
	points[0] = pointsOriginal[0] = sf::Vector2f(width, 0);
	points[0] = pointsOriginal[0] = sf::Vector2f(width, height);
	points[0] = pointsOriginal[0] = sf::Vector2f(0, height);
	for (const sf::Vector2f& vec : points)
		debugDrawPoints.append(sf::Vertex(vec, sf::Color::Blue));
}

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
	for (std::vector<sf::Vector2f>::const_iterator it = points.begin() + 1, end = points.end(); it != end; ++it)
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
			return intersectsPolygonOnPolygon(*this, (const PolygonMask&) other);
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
	for (std::vector<sf::Vector2f>::const_iterator it = points.begin() + 1, end = points.end(); it != end; ++it)
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

void PolygonMask::updateTransform(const sf::Transform& transform)
{
	const int size = pointsOriginal.size();
	for (int i = 0; i < size; ++i)
	{
		points[i] = transform.transformPoint(pointsOriginal[i]);
	}
}

#ifdef JE_DEBUG
void PolygonMask::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(debugDrawPoints, states);
}

void PolygonMask::setColor(sf::Color color)
{
	const int size = debugDrawPoints.getVertexCount();
	for (int i = 0; i < size; ++i)
		debugDrawPoints[i].color = color;
}
#endif

}