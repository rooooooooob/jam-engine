#include "Level.hpp"

#include <cstdlib>

namespace je
{

Level::Level(Game * const game, int width, int height)
	:width(width)
	,height(height)
	,game(game)
{
}

Level::Level(Game * const game, const std::string& filename, int width, int height)
	:width(width)
	,height(height)
	,game(game)
{
	//	TODO (max):
	//	load the code here and then call loadEntities() and loadTiles()
	//	based on the data loaded
}

Level::~Level()
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
        delete *it;
    entities.clear();
}

void Level::draw(sf::RenderTarget& target) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->draw(target);
	onDraw(target);
}

void Level::update()
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        (*it)->update();
        if ((*it)->isDead())
        {
            delete *it;
            *it = entities.back();
            entities.pop_back();
        }
        else
            ++it;
    }
	onUpdate();
}

Entity* Level::collision(const Entity *caller, Entity::Type type, float xoffset, float yoffset) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it != caller && (*it)->getType() == type && caller->intersects(**it, xoffset, yoffset))
            return *it;
    }
    return nullptr;
}

void Level::collision(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset, float yoffset) const
{
    results.clear();
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it != caller && (*it)->getType() == type && caller->intersects(**it, xoffset, yoffset))
            results.push_back(*it);
    }
}

void Level::addEntity(Entity *instance)
{
    entities.push_back(instance);
}

int Level::getWidth() const
{
    return width;
}

int Level::getHeight() const
{
    return height;
}

Game * const Level::getGame() const
{
	return game;
}

void Level::onUpdate()
{
	//	purposefully empty - meant for subclass-specific behaviour
}

void Level::onDraw(sf::RenderTarget& target) const
{
	//	purposefully empty - meant for subclass-specific behaviour
}

void Level::loadTiles(const std::string& layerName, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh, unsigned int const * const * tiles)
{
	//	TODO: create tilemaps here
}

void Level::loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes)
{
	//	purposefully empty - meant for subclass-specific behaviour
}

}
