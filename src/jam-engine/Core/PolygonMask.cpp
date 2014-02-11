#include "jam-engine/Core/PolygonMask.hpp"

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

bool PolygonMask::intersects(const PolygonMask& other) const
{
	int thisMin = 0, thisMax = 0, otherMin = 0, otherMax = 0;

	float angle = 0;

	int size = points.size();
	for (int i = 0; i < size; ++i)
	{
		angle = pointDirection(points[i], points[(i + 1) % size]);
		this->projectAgainstHyerplane(thisMin, thisMax, angle);
		other.projectAgainstHyerplane(otherMin, otherMax, angle);
		if (thisMin >= otherMax || thisMax < otherMin)
			return false;
	}

	size = other.points.size();
	for (int i = 0; i < size; ++i)
	{
		angle = pointDirection(other.points[i], other.points[(i + 1) % size]);
		this->projectAgainstHyerplane(thisMin, thisMax, angle);
		other.projectAgainstHyerplane(otherMin, otherMax, angle);
		if (thisMin >= otherMax || thisMax < otherMin)
			return false;
	}

	return true;
}

void PolygonMask::getAABB(sf::Rect<int>& out) const
{
	int maxX = out.left = points.front().x;
	int maxY = out.top = points.front().y;
	out.width = 0;
	out.height = 0;
	//	skip the first point since we already did that
	for (std::vector<sf::Vector2i>::const_iterator it = points.begin() + 1, end = points.end(); it != end; ++it)
	{
		if (it->x > maxX)
			maxX = it->x;
		if (it->x < out.left)
			out.left = it->x;
		if (it->y > maxY)
			maxY = it->y;
		if (it->y < out.top)
			out.top = it->y;
	}
	out.width = maxX - out.left;
	out.height = maxY - out.top;
}

}