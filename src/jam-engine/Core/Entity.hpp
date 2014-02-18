#ifndef JE_ENTITY_HPP
#define JE_ENTITY_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "jam-engine/Physics/CollisionMask.hpp"

namespace je
{

class Level;

class Entity
{
public:
	typedef std::string Type;
	virtual ~Entity();

#ifdef JE_DEBUG
	void debugDraw(sf::RenderTarget& target);
#endif
	virtual void draw(sf::RenderTarget& target, const sf::RenderStates &states = sf::RenderStates::Default) const = 0;
	void update();

	const Type& getType() const;

	bool isDead() const;

	int getDepth() const;

	void setDepth(int depth);
	/*
	 * Marks the Entity to be destroyed at the end of the current update
	 */
	void destroy();

	bool intersects(const sf::Rect<int>& bBox) const;

	inline bool intersects(const Entity& other, float xoffset = 0, float yoffset = 0) const;

	sf::Vector2i getDimensions() const;

	sf::Rect<int> getBounds() const;

	inline sf::Transformable& transform();

	inline const sf::Transformable& transform() const;

	//	equivalent to transform().getPosition(), but shorter
	inline const sf::Vector2f& getPos() const;

protected:
	Entity(Level * const level, const Type& type, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset = sf::Vector2i(0, 0));
	
	Entity(Level * const level, const Type& type, const sf::Vector2f& startPos, DetailedMask::MaskRef mask);
	
	virtual void onUpdate() = 0;

	//!The level the Entity is currently in
	Level * const level;

	sf::Vector2f prevPos;
	//!The drawing depth for the Entity. Larger depths are drawn first, so lower ones appear on top of higher ones
	int depth;

	void addAutoCollisionCheck(const std::string& type);



private:
	void updateMask();


	bool dead;
	const Type type;
	////!These are the physical dimensions of the Entity
	//sf::Vector2i dim;
	////!This is the offset from pos that the Entity's physical bounds is offset by for collisions
	//sf::Vector2i offset;
#ifdef JE_DEBUG
	sf::RectangleShape debugBounds;
#endif
	std::vector<std::string> autoCollisionChecks;

	CollisionMask collisionMask;
	sf::Transformable transformable;
	bool isTransformValid;
};

/*			inline implementation			*/
bool Entity::intersects(const Entity& other, float xoffset, float yoffset) const
{
	((Entity*)this)->updateMask();
	((Entity&)other).updateMask();
	return collisionMask.intersects(other.collisionMask);
}

sf::Transformable& Entity::transform()
{
	isTransformValid = false;
	return transformable;
}

const sf::Transformable& Entity::transform() const
{
	return transformable;
}

const sf::Vector2f& Entity::getPos() const
{
	return transformable.getPosition();
}

}

#endif
