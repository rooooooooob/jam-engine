#ifndef JE_TILEGRID_HPP
#define JE_TILEGRID_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace je
{

class TileGrid
{
public:
	TileGrid(int xOffset, int yOffset, int width, int height, int cellSizeX, int cellSizeY);
	~TileGrid();

	void setPos(int x, int y);

	void draw(sf::RenderTarget& target) const;

	void setTexture(int x, int y, const sf::Texture& texture);

	void setVisibleArea(const sf::Rect<int>& bBox);

private:
	void recalculateVisibleTiles();

	sf::Sprite **tiles;
	int left;       //  in pixels
	int top;        //  in pixels
	int width;      //  in tiles
	int height;     //  in tiles
	int cellSizeX;  //  in pixels
	int cellSizeY;  //  in pixels
	sf::Rect<int> bBox;
	sf::Rect<int> visibleTilesByIndices;
	sf::Rect<int> visibleTilesByPixels;
};

}

#endif
