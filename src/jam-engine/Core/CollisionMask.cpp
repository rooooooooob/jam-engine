#include "jam-engine/Core/CollisionMask.hpp"

namespace je
{

CollisionMask::CollisionMask(DetailedMask *mask)
	:detailedMask(std::move(mask))
{
	mask->getAABB(minX, maxX, minY, maxY);
}

void CollisionMask::updateTransform(const sf::Transform& transform)
{
	detailedMask->updateTransform(transform);
	detailedMask->getAABB(minX, maxX, minY, maxY);
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