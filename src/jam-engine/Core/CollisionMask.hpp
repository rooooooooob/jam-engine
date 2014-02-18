#ifndef JE_COLLISION_MASK_HPP
#define JE_COLLISION_MASK_HPP

#include <memory>

#include <SFML/Graphics/Transform.hpp>

#include "jam-engine/Core/DetailedMask.hpp"

namespace je
{

class CollisionMask
{
public:
	CollisionMask(DetailedMask* mask);

	inline bool intersects(const CollisionMask& other) const;

	void updateTransform(const sf::Transform& transform);

	// TODO : remove?
	int getWidth() const { return maxX - minX; }
	int getHeight() const { return maxY - minY; }

#ifdef JE_DEBUG
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setColor(sf::Color color);
#endif

//private:

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