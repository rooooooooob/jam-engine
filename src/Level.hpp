#ifndef JE_LEVEL_HPP
#define JE_LEVEL_HPP

#include <vector>
#include "Entity.hpp"

namespace je
{

class Game;

class Level
{
    public:
        Level(Game * const game, int width, int height);
        virtual ~Level();

        void draw(sf::RenderTarget& target) const;
        void update();


        Entity* collision(const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0) const;
        void collision(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0) const;
        void addEntity(Entity *instance);

        int getWidth() const;
        int getHeight() const;
		
		Game * const getGame() const;

	protected:
		virtual void onUpdate();
		virtual void onDraw();

    private:
        std::vector<Entity*> entities;
        int width;
        int height;
		Game * const game;
};

}

#endif
