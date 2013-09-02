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
{
}

Entity::~Entity()
{
}

const std::string& Entity::getType() const
{
	return type;
}

bool Entity::isDead() const
{
    return dead;
}

void Entity::destroy()
{
    dead = true;
}

bool Entity::intersects(const Entity& other, float xoffset, float yoffset) const
{
    const int left      = pos.x + offset.x + xoffset,     oleft   = other.pos.x + other.offset.x;
    const int right     = left + dim.x + xoffset,         oright  = oleft + other.dim.x;
    const int top       = pos.y + offset.y + yoffset,     otop    = other.pos.y + other.offset.y;
    const int bottom    = top + dim.y + yoffset,          obottom = otop + other.dim.y;
    return (left <= oright && right > oleft && top <= obottom && bottom > otop);
}

}
