#ifndef JE_COLLISION_CHECKING_IMPLEMENTATION_HPP
#define JE_COLLISION_CHECKING_IMPLEMENTATION_HPP

namespace je
{

class PolygonMask;

class CircleMask;

bool intersectsPolygonOnPolygon(const PolygonMask& a, const PolygonMask& b);

bool intersectsPolygonOnCircle(const PolygonMask& polygon, const CircleMask& circle);

}

#endif