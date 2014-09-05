#include "jam-engine/Core/Entity.hpp"

#include "jam-engine/Core/Game.hpp"
#include "jam-engine/Core/Level.hpp"
#include "jam-engine/Physics/PolygonMask.hpp"

namespace je
{

Entity::Entity(Level * const level, const Type& type, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset)
	:level(level)
	,type(type)
	,prevPos(startPos)
	,depth(0)
	,dead(false)
#ifdef JE_DEBUG
	,debugBounds()
#endif // JE_DEBUG
	,collisionMask(std::move(DetailedMask::MaskRef(new PolygonMask(dim.x, dim.y))))
	,transformable()
	,isTransformValid(true)
{
	transform().setPosition(startPos);
	transform().setOrigin(-offset.x, -offset.y);
#ifdef JE_DEBUG
	debugBounds.setFillColor(sf::Color::Transparent);
	debugBounds.setOutlineColor(sf::Color::Red);
	debugBounds.setOutlineThickness(1);
	debugBounds.setSize(sf::Vector2f(dim.x, dim.y));
	debugBounds.setPosition(sf::Vector2f(startPos.x - offset.x, startPos.y - offset.y));
#endif // JE_DEBUG
}

Entity::Entity(Level * const level, const Type& type, const sf::Vector2f& startPos, DetailedMask::MaskRef mask)
	:level(level)
	,type(type)
	,prevPos(startPos)
	,depth(0)
	,dead(false)
#ifdef JE_DEBUG
	,debugBounds()
#endif // JE_DEBUG
	,collisionMask(std::move(mask))
	,transformable()
	,isTransformValid(true)
{
	transform().setPosition(startPos);
#ifdef JE_DEBUG
	debugBounds.setFillColor(sf::Color::Transparent);
	debugBounds.setOutlineColor(sf::Color::Red);
	debugBounds.setOutlineThickness(1);
#endif // JE_DEBUG
}

Entity::~Entity()
{
}

#ifdef JE_DEBUG
void Entity::debugDraw(sf::RenderTarget& target)
{
	//- transform().getOrigin()
	const Game& game = level->getGame();
	if (game.getDebugCollisionDrawAABB())
	{
		debugBounds.setPosition(collisionMask.minX, collisionMask.minY);
		debugBounds.setSize(sf::Vector2f(collisionMask.getWidth(), collisionMask.getHeight()));
		target.draw(debugBounds);
	}
	if (game.getDebugCollisionDrawDetails())
	{
		sf::RenderStates states = sf::RenderStates::Default;
		//states.transform *= transform().getTransform();
		collisionMask.draw(target, states);
	}
}
#endif

void Entity::update()
{
	this->updateMask();
	this->onUpdate();

	for (const std::string typeName : autoCollisionChecks)
	{
		if (level->testCollision(this, typeName, 0, 0))
		{
			transform().setPosition(prevPos);
			break;
		}
	}
	prevPos = getPos();
}

const std::string& Entity::getType() const
{
	return type;
}

bool Entity::isDead() const
{
	return dead;
}

int Entity::getDepth() const
{
	return depth;
}

void Entity::setDepth(int depth)
{
	this->depth = depth;
}

void Entity::destroy()
{
	dead = true;
}

bool Entity::intersects(const sf::Rect<int>& bBox) const
{
	return collisionMask.intersects(bBox);
}

sf::Vector2i Entity::getDimensions() const
{
	return sf::Vector2i(collisionMask.getWidth(), collisionMask.getHeight());
}

sf::Rect<int> Entity::getBounds() const
{
	return sf::Rect<int>(sf::Vector2i(getPos() - transform().getOrigin()), getDimensions());
}

/*		protected		*/
void Entity::addAutoCollisionCheck(const std::string& type)
{
	for (const std::string& str : autoCollisionChecks)
		if (str == type)
			return;
	autoCollisionChecks.push_back(type);
}

/*		private			*/
void Entity::updateMask()
{
	if (!isTransformValid)
	{
		collisionMask.updateTransform(transform().getTransform());
		isTransformValid = true;
	}
}

}
