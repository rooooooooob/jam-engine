#ifndef JE_ENTITY_HPP
#define JE_ENTITY_HPP

#include <string>
#include <SFML/Graphics.hpp>

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
	virtual void draw(sf::RenderTarget& target) const = 0;
	virtual void update() = 0;

	const Type& getType() const;

	bool isDead() const;

	int getDepth() const;

	void setDepth(int depth);

	const sf::Vector2f& getPos() const;
	/*
	 * Marks the Entity to be destroyed at the end of the current update
	 */
	void destroy();

	bool intersects(const Entity& other, float xoffset = 0, float yoffset = 0) const;

	void setOffset(int x, int y);

	void setDimensions(int width, int height);

protected:
	Entity(Level * const level, const Type& type, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset = sf::Vector2i(0, 0));


	//!The level the Entity is currently in
	Level * const level;
	//!The Entity's current position in the current Level
	sf::Vector2f pos;
	//!The drawing depth for the Entity. Larger depths are drawn first, so lower ones appear on top of higher ones
	int depth;

private:
	bool dead;
	const Type type;
	//!These are the physical dimensions of the Entity
	sf::Vector2i dim;
	//!This is the offset from pos that the Entity's physical bounds is offset by for collisions
	sf::Vector2i offset;
#ifdef JE_DEBUG
	sf::RectangleShape debugBounds;
#endif
};

}

#endif
