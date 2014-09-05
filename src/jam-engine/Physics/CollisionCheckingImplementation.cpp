#include "jam-engine/Physics/CollisionCheckingImplementation.hpp"

#include "jam-engine/Physics/CircleMask.hpp"
#include "jam-engine/Physics/PolygonMask.hpp"
#include "jam-engine/Utility/Trig.hpp"

namespace je
{

bool intersectsPolygonOnPolygon(const PolygonMask& a, const PolygonMask& b)
{
	double thisMin = 0, thisMax = 0, otherMin = 0, otherMax = 0;

	double angle = 0;

	int size = a.points.size();
	for (int i = 0; i < size; ++i)
	{
		angle = pointDirection(a.points[i], a.points[(i + 1) % size]) + 90.f;
		a.projectAgainstHyerplane(thisMin, thisMax, angle);
		b.projectAgainstHyerplane(otherMin, otherMax, angle);
		if (thisMin >= otherMax || thisMax < otherMin)
			return false;
	}

	size = b.points.size();
	for (int i = 0; i < size; ++i)
	{
		angle = pointDirection(b.points[i], b.points[(i + 1) % size]) + 90.f;
		a.projectAgainstHyerplane(thisMin, thisMax, angle);
		b.projectAgainstHyerplane(otherMin, otherMax, angle);
		if (thisMin >= otherMax || thisMax < otherMin)
			return false;
	}

	return true;
}

bool intersectsPolygonOnCircle(const PolygonMask& polygon, const CircleMask& circle)
{
	double thisMin = 0, thisMax = 0, otherMin = 0, otherMax = 0;

	double angle = 0;

	int size = polygon.points.size();
	for (int i = 0; i < size; ++i)
	{
		angle = pointDirection(polygon.points[i], polygon.points[(i + 1) % size]) + 90.f;
		polygon.projectAgainstHyerplane(thisMin, thisMax, angle);
		circle.projectAgainstHyerplane(otherMin, otherMax, angle);
		if (thisMin >= otherMax || thisMax < otherMin)
			return false;
	}
	return true;
}

bool intersectsCircleOnCircle(const CircleMask& a, const CircleMask& b)
{
	return je::length(a.getPos() - b.getPos()) <= a.getRadius() + b.getRadius();
}

} // je
