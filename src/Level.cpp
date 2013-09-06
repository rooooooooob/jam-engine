#include "Level.hpp"

#include <cstdlib>
#include "TexManager.hpp"

namespace je
{

Level::Level(Game * const game, int width, int height)
	:width(width)
	,height(height)
	,game(game)
{
	tileSprites.push_back(sf::Sprite());	//	empty tile
}

Level::Level(Game * const game, const std::string& filename, int width, int height)
	:width(width)
	,height(height)
	,game(game)
{
	tileSprites.push_back(sf::Sprite());	//	empty tile
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

Entity* Level::testCollision(const Entity *caller, Entity::Type type, float xoffset, float yoffset) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it != caller && (*it)->getType() == type && caller->intersects(**it, xoffset, yoffset))
            return *it;
    }
    return nullptr;
}

void Level::findCollisions(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset, float yoffset) const
{
	//	TODO: ADD CULLING
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

const sf::Rect<int>& Level::getCameraBounds() const
{
	return cameraBounds;
}
	
void Level::setCameraBounds(const sf::Rect<int>& newBounds)
{
	cameraBounds = newBounds;
}

sf::Vector2f Level::getCameraPosition() const
{
	return sf::Vector2f(cameraBounds.left, cameraBounds.top);
}

void Level::setCameraPosition(const sf::Vector2f& cameraPosition)
{
	cameraBounds.left = cameraPosition.x;
	cameraBounds.top = cameraPosition.y;
}

void Level::moveCamera(const sf::Vector2f& cameraPosition)
{
	cameraBounds.left += cameraPosition.x;
	cameraBounds.top += cameraPosition.y;
}


/*		protected			*/

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
	tileLayers[layerName] = new TileGrid(this, 0, 0, tilesAcross, tilesHigh, tileWidth, tileHeight);
	TileGrid* grid = tileLayers[layerName];
	for (int x = 0; x < tilesAcross; ++x)
	{
		for (int y = 0; y < tilesHigh; ++y)
		{
			if (tiles[x][y])
				grid->setTexture(x, y, tileSprites[tiles[x][y]]);
		}
	}
	this->addEntity(grid);
}

void Level::loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes)
{
	//	purposefully empty - meant for subclass-specific behaviour
}

void Level::createTiles(const std::string& filename, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh)
{
	const sf::Texture& texture = TexManager::get(filename);
	for (int x = 0; x < tilesAcross; ++x)
	{
		for (int y = 0; y < tilesHigh; ++y)
		{
			tileSprites.push_back(sf::Sprite(texture));
			tileSprites.back().setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
		}
	}
}

}
