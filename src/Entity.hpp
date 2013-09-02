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

        virtual void draw(sf::RenderTarget& target) const = 0;
        virtual void update() = 0;

        const Type& getType() const;
        bool isDead() const;
        void destroy();
        bool intersects(const Entity& other, float xoffset = 0, float yoffset = 0) const;

    protected:
        Entity(Level * const stage, const Type& type, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset = sf::Vector2i(0, 0));

        Level * const level;
        sf::Vector2f pos;
        const sf::Vector2i dim;
        const sf::Vector2i offset;
    private:
        bool dead;
		const Type type;
};

}

#endif
