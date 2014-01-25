#include "jam-engine/Graphics/TileGrid.hpp"

#include <cassert>
#include <iostream>
namespace je
{

TileGrid::TileGrid(Level * const level, int xOffset, int yOffset, int width, int height, int cellSizeX, int cellSizeY)
	:Entity(level, "TileGrid", sf::Vector2f(xOffset, yOffset), sf::Vector2i(width * cellSizeX, height * cellSizeY))
	,left(xOffset)
	,top(yOffset)
	,width(width)
	,height(height)
	,cellSizeX(cellSizeX)
	,cellSizeY(cellSizeY)
	,bBox(xOffset, yOffset, width * cellSizeX, height * cellSizeY)
{
	depth = 1;	//	just so that if the user doesn't specify, at least Entities will go above it by default
	tiles = new sf::Sprite**[width];
	for (int i = 0; i < width; ++i)
	{
		tiles[i] = new sf::Sprite*[height];
		for (int j = 0; j < height; ++j)
		{
			//tiles[i][j].setPosition(xOffset + i * cellSizeX, yOffset + j * cellSizeY);
			tiles[i][j] = nullptr;
		}
	}
	this->recalculateVisibleTiles();
}

TileGrid::~TileGrid()
{
	for (int i = 0; i < width; ++i)
	{
		//	no need, TileGrid doesn't own these
		/*for (int j = 0; j < height; ++j)
			if (tiles[i][j])
				delete tiles[i][j];*/
		delete[] tiles[i];
	}
	delete[] tiles;
}

void TileGrid::setPos(int x, int y)
{
	const int diffX = x - left;
	const int diffY = y - top;
	if (diffX || diffY)
	{
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				if (tiles[i][j])
					tiles[i][j]->setPosition(x, y);
			}
		}
		left = x;
		top = y;

		pos.x = x;
		pos.y = y;

		this->recalculateVisibleTiles();
	}
}

void TileGrid::draw(sf::RenderTarget& target, const sf::RenderStates &states /*= sf::RenderStates::Default*/) const
{
	for (int i = visibleTilesByIndices.left; i < visibleTilesByIndices.width; ++i)
	{
		for (int j = visibleTilesByIndices.top; j < visibleTilesByIndices.height; ++j)
		{
			if (tiles[i][j])
			{
				tiles[i][j]->setPosition(left + i * cellSizeX, top + j * cellSizeY);
				target.draw(*tiles[i][j], states);
			}
		}
	}
}

void TileGrid::onUpdate()
{
}

void TileGrid::setTexture(int x, int y, sf::Sprite& sprite)
{
	assert(x >= 0 && x < width && y >= 0 && y < height);
	tiles[x][y] = &sprite;
}

void TileGrid::setVisibleArea(const sf::Rect<int>& bBox)
{
	if (this->bBox != bBox)
	{
		this->bBox = bBox;
		this->recalculateVisibleTiles();
	}
}

/*	  TileGrid private methods		*/
void TileGrid::recalculateVisibleTiles()
{
	visibleTilesByIndices.left = 0;
	visibleTilesByIndices.top = 0;
	visibleTilesByIndices.width = width;
	visibleTilesByIndices.height = height;

	//  If the new minimum/maxiumums are valid (not outside the grid) then update them
	if (bBox.left - left > 0)
	{
		visibleTilesByIndices.left = (bBox.left - left) / cellSizeX;
	}

	if ((bBox.left + bBox.width - left) / cellSizeX < width)
	{
		visibleTilesByIndices.width = (bBox.left + bBox.width - left) / cellSizeX + 1;
	}

	if (bBox.top - top > 0)
	{
		visibleTilesByIndices.top = (bBox.top - top) / cellSizeY;
	}

	if ((bBox.top + bBox.height - top) / cellSizeY < height)
	{
		visibleTilesByIndices.height = (bBox.top + bBox.height - top) / cellSizeY + 1;
	}

	visibleTilesByPixels.left = left + visibleTilesByIndices.left * cellSizeX;
	visibleTilesByPixels.top = top + visibleTilesByIndices.top * cellSizeY;
	visibleTilesByPixels.width = visibleTilesByIndices.width * cellSizeX;
	visibleTilesByPixels.height = visibleTilesByIndices.height * cellSizeY;
}

}
