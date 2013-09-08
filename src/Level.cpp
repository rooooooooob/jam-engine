#include "Level.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "TexManager.hpp"
#include "Game.hpp"

namespace je
{

Level::Level(Game * const game, int width, int height)
	:width(width)
	,height(height)
	,game(game)
{
	tileSprites.push_back(sf::Sprite());	//	empty tile
}

Level::Level(Game * const game, const std::string& filename)
	:width(0)
	,height(0)
	,game(game)
{
	tileSprites.push_back(sf::Sprite());	//	empty tile (0)
}

Level::~Level()
{
	this->clear();
}

void Level::draw(sf::RenderTarget& target) const
{
    for (int i = 0; i < entities.size(); ++i)
	{
		entities[i]->draw(target);
#ifdef JE_DEBUG
		entities[i]->debugDraw(target);
#endif // JE_DEBUG
	}
	onDraw(target);
	/*std::cout << "tileSprites.size() = " << tileSprites.size() << "\n";
	for (int i = 0; i < tileSprites.size(); ++i)
	{
		sf::Sprite& s = tileSprites[i];
		//std::cout << "(" << s.getGlobalBounds().width << "," << s.getGlobalBounds().height << ")";
		tileSprites[i].setPosition(sf::Vector2f(i * 16, 0));
		target.draw(tileSprites[i]);
	}*/
}

void Level::update()
{
    for (int i = 0; i < entities.size(); )
    {
        entities[i]->update();
        if (entities[i]->isDead())
        {
            delete entities[i];
            entities[i] = entities.back();
            entities.pop_back();
        }
        else
            ++i;
    }
	onUpdate();
	for (auto& grid : tileLayers)
	{
		sf::Rect<int> bounds(cameraBounds);
		bounds.left -= cameraBounds.width / 2;
		bounds.top -= cameraBounds.height / 2;
		grid.second->setVisibleArea(bounds);
	}
	std::sort(entities.begin(), entities.end(), [] (const Entity *a, const Entity *b) -> bool {
		return a->getDepth() > b->getDepth();
	});
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

void Level::clear()
{
	for (Entity *entity : entities)
		delete entity;
	entities.clear();
	tileLayers.clear();
    tileSprites.clear();
}

void Level::clearEntities()
{
	bool isTile = false;
	for (int i = 0; i < entities.size(); ++i)
	{
		isTile = false;
		for (auto& it : tileLayers)
		{
			if (entities[i] == it.second)
			{
				isTile = true;
				break;
			}
		}
		if (!isTile)
		{
			delete entities[i];
			entities[i] = entities.back();
			entities.pop_back();
			--i;
		}
	}
}

int Level::getWidth() const
{
    return width;
}

int Level::getHeight() const
{
    return height;
}

Game& Level::getGame() const
{
	return *game;
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

sf::Vector2f Level::getCursorPos() const
{
	sf::Vector2i posI = game->getWindow().mapCoordsToPixel(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) - game->getWindow().getPosition();
	return sf::Vector2f(posI.x + cameraBounds.left - cameraBounds.width / 2, posI.y + cameraBounds.top - cameraBounds.height / 2);
}

void Level::loadMap(const std::string& filename)
{
	    using namespace rapidxml;
    std::ifstream mapFile (filename);
    std::string line;
    std::stringstream ss;
    std::cout << filename << "\n";

    if (mapFile.is_open())
    {
        while (mapFile.good())
        {
            getline (mapFile, line);
            ss << line << "\n";
        }

        std::string s = ss.str();
        std::vector<char> text(s.begin(), s.end());
        text.push_back('\0');

       	xml_document<> doc;
        doc.parse<0> (text.data());

        xml_node<> *root = doc.first_node("map");
        if (root)
        {
            xml_attribute<> *attr = root->first_attribute("version");
            std::string version = attr->value();
            std::cout << attr->value() << "\n";
            attr = attr->next_attribute("orientation");
            std::cout << attr->value() << "\n";
            std::string orientation = attr->value();
            attr = attr->next_attribute("width");
            std::cout << attr->value() << "\n";
            int mapWidth = atoi(attr->value());
            attr = attr->next_attribute("height");
            std::cout << attr->value() << "\n";
            int mapHeight = atoi(attr->value());
            attr = attr->next_attribute("tilewidth");
            std::cout << attr->value() << "\n";
            int tileWidth = atoi(attr->value());
            attr = attr->next_attribute("tileheight");
            std::cout << attr->value() << "\n";
            int tileHeight = atoi(attr->value());

			width = mapWidth * tileWidth;
			height = mapHeight * tileHeight;

            for (xml_node<> *tileset = root->first_node("tileset"); tileset; tileset = tileset->next_sibling("tileset"))
            {
                xml_attribute<> *attr = tileset->first_attribute("firstgid");
                std::cout << attr->value() << "\n";
                int firstgrid = atoi(attr->value());
                attr = attr->next_attribute("name");
                std::cout << attr->value() << "\n";
                std::string tileSetName = attr->value();
                attr = attr->next_attribute("tilewidth");
                std::cout << attr->value() << "\n";
                int tileSet_tileWidth = atoi(attr->value());
                attr = attr->next_attribute("tileheight");
                std::cout << attr->value() << "\n";
                int tileSet_tileHeight = atoi(attr->value());
                std::cout << "tileSetH: " << tileSet_tileHeight << "  tileSetW: " << tileSet_tileWidth << "\n";


                xml_node<> *img = tileset->first_node ("image");
                attr = img->first_attribute ("source");
                std::cout << attr->value() << "\n";
                std::string source = attr->value();
                attr = attr->next_attribute ("width");
                std::cout << attr->value() << "\n";
                int imgWidth = atoi(attr->value());
                attr = attr->next_attribute ("height");
                std::cout << attr->value() << "\n";
                int imgHeight = atoi(attr->value());
                createTiles(source, tileSet_tileHeight, tileSet_tileWidth, height, width);
            }

            for (xml_node<> *layer = root->first_node("layer"); layer; layer = layer->next_sibling("layer"))
            {
                xml_attribute<> *attr = layer->first_attribute();
                std::cout << "fgdsg" << attr->value() << "\n";
                std::string tileLayerName = attr->value();
                attr = attr->next_attribute();
                std::cout << attr->value() << "\n";
                int layerWidth = atoi(attr->value());
                attr = attr->next_attribute();
                std::cout << attr->value() << "\n";
                int layerHeight = atoi(attr->value());
                xml_node<> *layerData = layer->first_node("data");
                attr = layerData->first_attribute();
                std::cout << attr->value() << "\n";
                std::string encodeMode = attr->value();

                std::string tileFieldText = layerData->value();
                std::stringstream sstream (tileFieldText);
                std::string fieldValue;

                unsigned int **tileLayer = new unsigned int* [layerWidth];
                for(int g = 0; g < layerWidth; ++g)
                {
                    tileLayer[g] = new unsigned int[layerHeight];
                }
                std::cout << "\n\n---height: " << tileHeight << "   width: " << tileWidth << "\n";

                int i = 0;
                int j = 0;

                while (std::getline(sstream, fieldValue, ','))
                {
                    //std::cout << "i: " << i << "  j: " << j << "\n";
                    tileLayer[j][i] = atoi (fieldValue.c_str());
                    ++j;
                    if (j == layerWidth)
                    {
                        //std::cout << "\n";
                        j = 0;
                        ++i;
                    }
                }
                //std::cout << "\n";
				this->transformTiles(tileLayerName, layerWidth, layerHeight, tileLayer);
                loadTiles(tileLayerName, tileWidth, tileHeight, layerWidth, layerHeight, tileLayer);
                /*for (int a = 0; a < layerHeight; ++a)
                {
                    for (int b = 0; b < layerWidth; ++b)
                    {
                        std::cout << (tileLayer[a][b] ? "X" : " ");
                    }
                    std::cout << "\n";
                }*/
            }

            std::cout << "test\n";
            for (xml_node<> *objectgroup = root->first_node("objectgroup"); objectgroup; objectgroup = objectgroup->next_sibling("objectgroup"))
            {
                std::cout << "test2\n";
                xml_attribute<> *attr = objectgroup->first_attribute ("name");
                std::cout << attr->value() << "\n";
                std::string objectLayer_name = attr->value();
                attr = attr->next_attribute ("width");
                std::cout << attr->value() << "\n";
                int objectLayer_Width = atoi(attr->value());
                attr = attr->next_attribute ("height");
                std::cout << attr->value() << "\n";
                int objectLayer_Height = atoi(attr->value());

                std::vector<EntityPrototype> prototypes;

                for (xml_node<> *obj = objectgroup->first_node("object"); obj; obj = obj->next_sibling("object"))
                {
					prototypes.push_back(EntityPrototype());
                    EntityPrototype& prototype = prototypes.back();

                    //std::cout << obj->name();
                    xml_attribute<> *attr = obj->first_attribute("gid");
                    if (attr)
                    {
                        //std::cout << attr->value() << "\n";
                        int gid = atoi (attr->value());
                        prototype.id = gid;
                    }
                    //else
                        //std::cout << "nigga u broke obj's gid attribute\n";

                    attr = obj->first_attribute ("x");
                    if (attr)
                    {
                        //std::cout << attr->value() << "\n";
                        int x = atoi (attr->value());
                        prototype.x = x;
                    }
                    //else
                        //std::cout << "nigga u broke obj's x attribute\n";

                    attr = obj->first_attribute ("y");
                    if (attr)
                    {
                        //std::cout << attr->value() << "\n";
                        int y = atoi (attr->value());
                        prototype.y = y;
                    }
                    //else
                        //std::cout << "nigga u broke obj's y attribute\n";

                    attr = obj->first_attribute ("width");
                    if (attr)
                    {
                        //std::cout << attr->value() << "\n";
                        int objWidth = atoi (attr->value());
                    }
                    //else
                        //std::cout << "nigga u broke obj's width attribute\n";

                    attr = obj->first_attribute ("height");
                    if (attr)
                    {
                        //std::cout << attr->value() << "\n";
                        int objHeight = atoi (attr->value());
                    }
                    //else
                        //std::cout << "nigga u broke obj's height attribute\n";

					attr = obj->first_attribute("name");
					if (attr)
					{
						prototype.name = attr->value();
					}
					attr = obj->first_attribute("type");
					if (attr)
					{
						prototype.type = attr->value();
					}
                }
                if (!prototypes.empty())
					this->loadEntities(objectLayer_name, prototypes);
            }
        }
        else
            std::cout << "nigga u broke somthin' in da map\n";
    }
    else
    {
        std::cout << "couldn't open map\n";
    }
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

void Level::drawGUI(sf::RenderTarget& target) const
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
            //std::cout << "x: " << x << "  y: " << y << "\n";
            //std::cout << (tiles[x][y] ? "X" : " ");
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
	std::cout << "tileWidth : " << tileWidth << "\nTileHeight" << tileHeight << "\n";
	const sf::Texture& texture = getGame().getTexManager().get(filename);
	const int w = texture.getSize().x / tileWidth;
	const int h = texture.getSize().y / tileHeight;
	std::cout << "should create " << w * h << " sprites created\n";
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
		    //std::cout << "x:" << x << "  y: " << y << "\n";
			tileSprites.push_back(sf::Sprite(texture));
			tileSprites.back().setTextureRect(sf::IntRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight));
		}
	}
    std::cout << "\n";
}

void Level::transformTiles(const std::string& layerName, int tilesAcross, int tilesHigh, unsigned  **tiles)
{
	std::cout << "Level::transformTiles()\n";
	//	no transform is done here
}

}
