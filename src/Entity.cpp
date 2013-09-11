#include "Entity.hpp"

#include "Level.hpp"

namespace je
{

Entity::Entity(Level * const level, const Type& type, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset)
    :level(level)
	,type(type)
    ,pos(startPos)
    ,dim(dim)
    ,offset(offset)
    ,dead(false)
#ifdef JE_DEBUG
	,debugBounds()
#endif // JE_DEBUG
{
#ifdef JE_DEBUG
	debugBounds.setFillColor(sf::Color::Transparent);
	debugBounds.setOutlineColor(sf::Color::Red);
	debugBounds.setOutlineThickness(1);
	debugBounds.setSize(sf::Vector2f(dim.x, dim.y));
	debugBounds.setPosition(sf::Vector2f(pos.x - offset.x, pos.y - offset.y));
#endif // JE_DEBUG
}

Entity::~Entity()
{
}

#ifdef JE_DEBUG
void Entity::debugDraw(sf::RenderTarget& target)
{
	debugBounds.setPosition(pos.x + offset.x, pos.y + offset.y);
	target.draw(debugBounds);
}
#endif

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

const sf::Vector2f& Entity::getPos() const
{
	return pos;
}

void Entity::destroy()
{
    dead = true;
}

bool Entity::intersects(const Entity& other, float xoffset, float yoffset) const
{
    const int left      = pos.x + offset.x + xoffset,     oleft   = other.pos.x + other.offset.x;
    const int right     = left + dim.x,                   oright  = oleft + other.dim.x;
    const int top       = pos.y + offset.y + yoffset,     otop    = other.pos.y + other.offset.y;
    const int bottom    = top + dim.y,                    obottom = otop + other.dim.y;
    return (left <= oright && right > oleft && top <= obottom && bottom > otop);
}

void Entity::setOffset(int x, int y)
{
	offset.x = x;
	offset.y = y;
#ifdef JE_DEBUG
	debugBounds.setPosition(pos.x - offset.x, pos.y - offset.y);
#endif // JE_DEBUG
}

void Entity::setDimensions(int width, int height)
{
	dim.x = width;
	dim.y = height;
#ifdef JE_DEBUG
	debugBounds.setSize(sf::Vector2f(dim.x, dim.y));
#endif // JE_DEBUG
}
sf::Rect<int> Entity::getBounds() const
{
	return sf::Rect<int>(pos.x + offset.x, pos.y + offset.y, dim.x, dim.y);
}

}
