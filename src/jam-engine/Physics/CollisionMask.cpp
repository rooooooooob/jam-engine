#include "jam-engine/Physics/CollisionMask.hpp"

namespace je
{

CollisionMask::CollisionMask(DetailedMask::MaskRef mask)
	:detailedMask(std::move(mask))
{
	detailedMask->getAABB(minX, maxX, minY, maxY);
}

void CollisionMask::updateTransform(const sf::Transform& transform)
{
	detailedMask->updateTransform(transform);
	detailedMask->getAABB(minX, maxX, minY, maxY);
}

CollisionMask& CollisionMask::operator=(const CollisionMask& rhs)
{
	detailedMask = rhs.detailedMask->clone();
	detailedMask->getAABB(minX, maxX, minY, maxY);
	return *this;
}

#ifdef JE_DEBUG
void CollisionMask::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	detailedMask->draw(target, states);
}

void CollisionMask::setColor(sf::Color color)
{
	detailedMask->setColor(color);
}
#endif

}