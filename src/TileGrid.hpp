#ifndef JE_TILEGRID_HPP
#define JE_TILEGRID_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Entity.hpp"

namespace je
{

class TileGrid : public Entity
{
public:
	TileGrid(Level * const level, int xOffset, int yOffset, int width, int height, int cellSizeX, int cellSizeY);
	~TileGrid();

	void setPos(int x, int y);

	void onUpdate() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates &states = sf::RenderStates::Default) const override;

	void setTexture(int x, int y, sf::Sprite& sprite);

	void setVisibleArea(const sf::Rect<int>& bBox);

private:
	void recalculateVisibleTiles();

	sf::Sprite ***tiles;
	int left;	   //  in pixels
	int top;		//  in pixels
	int width;	  //  in tiles
	int height;	 //  in tiles
	int cellSizeX;  //  in pixels
	int cellSizeY;  //  in pixels
	sf::Rect<int> bBox;
	sf::Rect<int> visibleTilesByIndices;
	sf::Rect<int> visibleTilesByPixels;
};

}

#endif
