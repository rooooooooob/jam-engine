#ifndef JE_LEVEL_HPP
#define JE_LEVEL_HPP

#include <vector>
#include <string>
#include <map>
#include <initializer_list>
#include <SFML/Graphics/RenderStates.hpp>
#include "rapidxml.hpp"
#include "Entity.hpp"
#include "TileGrid.hpp"

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
	 */
	Level(Game * const game, const std::string& filename);

	virtual ~Level();

	void draw(sf::RenderTarget& target) const;

	virtual void drawGUI(sf::RenderTarget& target) const;


	void update();

	Entity* testCollision(const sf::Rect<int>& bBox, Entity::Type type);

	/**
	 * Queries the level for collisions and stops after the first one
	 * @param caller The Entity to use a reference to query from
	 * @param type The type of Entity to query for
	 * @param xoffset The horizontal offset away from caller to query at
	 * @Param yoffset The vertical offset away from caller to query at
	 * @return The first Entity found that collides, or nullptr if none were found
	 */
	Entity* testCollision(const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0);

	/**
	 * Queries the level for collisions
	 * @param results The vector to which the collisions are stored in. (the vector is cleared at the start)
	 * @param caller The Entity to use a reference to query from
	 * @param type The type of Entity to query for
	 * @param xoffset The horizontal offset away from caller to query at
	 * @Param yoffset The vertical offset away from caller to query at
	 */
	void findCollisions(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0);

	/**
	 * Adds an Entity into the Level. The Level now assumes ownership of the Entity
	 * @param instance The Entity to add
	 */
	void addEntity(Entity *instance);

	/**
	 * Destroys everything in the level
	 */
	void clear();

	/**
	 * Destroys the non-tile layer Entities in the level
	 */
	void clearEntities();

	int getWidth() const;

	int getHeight() const;

	Game& getGame() const;

	sf::Rect<int> getCameraBounds() const;

	void setCameraBounds(const sf::Rect<int>& newBounds);

	sf::Vector2f getCameraPosition() const;

	void setCameraPosition(const sf::Vector2f& cameraPosition);

	void moveCamera(const sf::Vector2f& cameraPosition);

	sf::Vector2f getCursorPos() const;

	void loadMap(const std::string& filename);

	void debugDrawRect(const sf::Rect<int>& rect, sf::Color outlineColor, sf::Color fillColor = sf::Color::Transparent, int outlineThickness = 1);

	/**
	 * Sets the order of any Entities which are to be updated before all others
	 * All Entities in this category will be updated in the order they are set in this
	 * initializer list. The order of things outside of here is lexicographical.
	 * @param order The order for entities in this category
	 */
	void setSpecificOrderEntitiesPre(std::initializer_list<std::string> order);

	/**
	 * Sets the order of any Entities which are to be updated after all others
	 * All Entities in this category will be updated in the order they are set in this
	 * initializer list. The order of things outside of here is lexicographical.
	 * @param order The order for entities in this category
	 */
	void setSpecificOrderEntitiesPost(std::initializer_list<std::string> order);

protected:
	/**
	 * Represents the data loaded from a Tiled map file. loadEntities should
	 * be overridden to read a vector of EntityPrototypes and create actual
	 * Entity objects out of them.
	 */
	struct EntityPrototype
	{
		EntityPrototype()
			:id(-1)
			,x(-1)
			,y(-1)
			,name("")
			,type("")
		{
		}

		unsigned int id;	//	Tiled object gid
		int x, y;			//	position
		std::string name;	//	tiled name field
		std::string type;	//	tiled type field
	};

	virtual void onUpdate();

	virtual void onDraw(sf::RenderTarget& target) const;

	virtual void beforeDraw(sf::RenderTarget& target) const;

	/**
	 * Defines how to handle the tile layers when maps are loaded. If this isn't overridden
	 * then TileMaps will be created and added to the level using layerName as the texture filename.
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

	virtual void createTiles(const std::string& filename, int tileWidth, int tileHeight, int tilesAcross, int tilesHigh);

	virtual void transformTiles(const std::string& layerName, int tilesAcross, int tilesHigh, unsigned  **tiles);



	std::map<std::string, std::vector<Entity*> > entities;
	std::map<std::string, TileGrid*> tileLayers;
	sf::RenderStates states;

private:
	void init();
	void fixUpdateOrder();


	std::vector<sf::Sprite> tileSprites;
	sf::Rect<int> cameraBounds;
	int width;
	int height;
	Game * const game;
	std::vector<Entity*> depthBuffer;
	std::vector<std::string> specificOrderEntitiesPre;
	std::vector<std::string> specificOrderEntitiesPost;
	std::map<std::string, bool> hasSpecificUpdateOrder;
#ifdef JE_DEBUG
	std::vector<sf::RectangleShape> debugDrawRects;
#endif
};

}

#endif
