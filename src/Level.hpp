#ifndef JE_LEVEL_HPP
#define JE_LEVEL_HPP

#include <vector>
#include <string>
#include "Entity.hpp"

namespace je
{

class Game;

class Level
{
public:
	/**
	 * Constructs an empty level with the given width and height
	 * @param game The game the level belongs to
	 * @param width The width of the level in pixels
	 * @param height The height of the level in pixels
	 */
	Level(Game * const game, int width, int height);
	/**
	 * Constructs a level with the given width and height using the passed in .tmx file
	 * @param game The game the level belongs to
	 * @param filename The .tmx file to load assets from
	 * @param width The width of the level in pixels (if -1 the largest tile layer width in the .tmx file will be used)
	 * @param height The height of the level in pixels (if -1 the largest tile layer height in the .tmx file will be used)
	 */
	Level(Game * const game, const std::string& filename, int width, int height);
	
	virtual ~Level();

	void draw(sf::RenderTarget& target) const;
	
	void update();

	/**
	 * Queries the level for collisions and stops after the first one
	 * @param caller The Entity to use a reference to query from
	 * @param type The type of Entity to query for
	 * @param xoffset The horizontal offset away from caller to query at
	 * @Param yoffset The vertical offset away from caller to query at
	 * @return The first Entity found that collides, or nullptr if none were found
	 */
	Entity* collision(const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0) const;

	/**
	 * Queries the level for collisions
	 * @param results The vector to which the collisions are stored in. (the vector is cleared at the start)
	 * @param caller The Entity to use a reference to query from
	 * @param type The type of Entity to query for
	 * @param xoffset The horizontal offset away from caller to query at
	 * @Param yoffset The vertical offset away from caller to query at
	 */
	void collision(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0) const;
	
	/**
	 * Adds an Entity into the Level. The Level now assumes ownership of the Entity
	 * @param instance The Entity to add
	 */
	void addEntity(Entity *instance);

	int getWidth() const;
	
	int getHeight() const;
		
	Game * const getGame() const;

protected:
	struct EntityPrototype
	{
		unsigned int id;
		int x, y;
		std::string name;
		std::string type;
	};
	
	virtual void onUpdate();
	
	virtual void onDraw(sf::RenderTarget& target) const;
	
	/**
	 * Defines how to handle the tile layers when maps are loaded. If this isn't overridden
	 * then TileMaps will be created and added to the level.
	 * @param layerName The layer's name
	 * @param tileWidth The width in pixels of each tile
	 * @param tileHeight The height in pixels of each tile
	 * @param tilesAcross How many tiles wide the layer is
	 * @param tilesHigh How many tiles high the layer is
	 * @param tiles A 2D array representing the tilemap (accessed [x][y])
	 */
	virtual void loadTiles(const std::string& layerName, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh, unsigned int const * const * tiles);
	/**
	 * Defines how to handles the object layers when maps are loaded. If this isn't overridden
	 * then nothing will happen (empty method)
	 * @param layerName The layer's name
	 * @param prototypes All the objects in the object layer
	 */
	virtual void loadEntities(const std::string& layerName, const std::vector<EntityPrototype>& prototypes);

private:
	std::vector<Entity*> entities;
	int width;
	int height;
	Game * const game;
};

}

#endif
