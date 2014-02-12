#ifndef JE_COLLISION_MASK_HPP
#define JE_COLLISION_MASK_HPP

#include <memory>

#include "jam-engine/Core/DetailedMask.hpp"

namespace je
{

class CollisionMask
{
public:
	CollisionMask();

	inline bool intersects(const CollisionMask& other) const;

private:
	int minX, maxX;
	int minY, maxY;
	std::unique_ptr<DetailedMask> detailedMask;
};

/*		inline implementation		*/

bool CollisionMask::intersects(const CollisionMask& other) const
{
	if (minX >= other.maxX || maxX < other.minX || minY >= other.maxY || maxY < other.minY)
		return false;
	return detailedMask->intersects(*other.detailedMask);
}


}

#endif