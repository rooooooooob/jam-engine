#include "jam-engine/Core/CollisionMask.hpp"

namespace je
{

CollisionMask::CollisionMask(DetailedMask *mask)
	:detailedMask(std::move(mask))
{
	mask->getAABB(minX, maxX, minY, maxY);
}

void CollisionMask::updateTransform()
{
	detailedMask->updateTransform(this->getTransform());
	detailedMask->getAABB(minX, maxX, minY, maxY);
}

#ifdef JE_DEBUG
void CollisionMask::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	detailedMask->draw(target, states);
}

void CollisionMask::setColor(sf::Color color)
{
	detailedMask->setColor(color);
}
#endif

}