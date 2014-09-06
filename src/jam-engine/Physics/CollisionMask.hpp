#ifndef JE_COLLISION_MASK_HPP
#define JE_COLLISION_MASK_HPP

#include <memory>

#include <SFML/Graphics/Transform.hpp>

#include "jam-engine/Physics/DetailedMask.hpp"

namespace je
{

class CollisionMask
{
public:
	CollisionMask(DetailedMask::MaskRef mask);

	inline bool intersects(const CollisionMask& other) const;

	inline bool intersects(const sf::Rect<int>& bBox) const
	{
		return bBox.left < maxX && bBox.left + bBox.width >= minX && bBox.top < maxY && bBox.top + bBox.height >= minY;
	}

	void updateTransform(const sf::Transform& transform);

	inline const DetailedMask& getDetails() const;

	// TODO : remove?
	int getWidth() const { return maxX - minX; }
	int getHeight() const { return maxY - minY; }

#ifdef JE_DEBUG
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setColor(sf::Color color);

	sf::Vector2f getDebugDrawPos() const { return sf::Vector2f(minX, minY); };
#endif

	CollisionMask& operator=(const CollisionMask& rhs);

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

const DetailedMask& CollisionMask::getDetails() const
{
	return *detailedMask;
}


}

#endif
