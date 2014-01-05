#include "PathGrid.hpp"

namespace je
{

const PathGrid::CellType PathGrid::canGoLeft  = 1;
const PathGrid::CellType PathGrid::canGoRight = 2;
const PathGrid::CellType PathGrid::canGoUp    = 4;
const PathGrid::CellType PathGrid::canGoDown  = 8;
const PathGrid::CellType PathGrid::canGoNW    = 16;
const PathGrid::CellType PathGrid::canGoNE    = 32;
const PathGrid::CellType PathGrid::canGoSW    = 64;
const PathGrid::CellType PathGrid::canGoSE    = 128;

/*			PathGrid::Node			*/
PathGrid::Node::Node(const PathGrid& owner, int x, int y)
	:owner(owner)
	,x(x)
	,y(y)
{
}

PathGrid::ID PathGrid::Node::getID() const
{
	return (x << 16) + y;
}

sf::Vector2f PathGrid::Node::getPos() const
{
	return sf::Vector2f((x + 0.5f) * owner.cellWidth, (y + 0.5f) * owner.cellHeight);
}

bool PathGrid::Node::operator==(const Node& rhs) const
{
	return x == rhs.x && y == rhs.y && &owner == &rhs.owner;
}

bool PathGrid::Node::operator<(const Node& rhs) const
{
	if (x < rhs.x)
		return true;
	if (x > rhs.x)
		return false;
	return y < rhs.y;
}


/*			PathGrid				*/
PathGrid::PathGrid(int cellWidth, int cellHeight, int width, int height, bool allowDiag, float diagRatio)
	:cellWidth(cellWidth)
	,cellHeight(cellHeight)
	,width(width)
	,height(height)
	,grid(width, height)
	,weights(width, height)
	,walkable(width, height)
	,allowDiag(allowDiag)
	,diagRatio(diagRatio)
{
	for (CellType& type : grid)
		type = 0xFF;	//	allow all paths
	for (float& weight : weights)
		weight = 1.f;
	for (bool& b : walkable)
		b = true;
}

void PathGrid::addPath(int x, int y, CellType type)
{
	grid.get(x, y) |= type;
}

void PathGrid::removePath(int x, int y, CellType type)
{
	grid.get(x, y) &= ~type;
}

void PathGrid::addAllPaths()
{
	for (CellType& type : grid)
		type = 0xFF;	//	allow all paths
}

void PathGrid::removeAllPaths()
{
	for (CellType& type : grid)
		type = 0;		//	disallow all paths
}

void PathGrid::openCell(int x, int y)
{
	walkable.get(x, y) = true;
	auto& g = grid.get(x, y);
	if (x > 0 && walkable.get(x -1 , y))
	{
		grid.get(x - 1, y) |= canGoRight;
		g |= canGoLeft;
	}
	if (x < width - 1 && walkable.get(x + 1, y))
	{
		grid.get(x + 1, y) |= canGoLeft;
		g |= canGoRight;
	}
	if (y > 0 && walkable.get(x, y - 1))
	{
		grid.get(x, y - 1) |= canGoDown;
		g |= canGoUp;
	}
	if (y < height - 1 && walkable.get(x, y + 1))
	{
		grid.get(x, y + 1) |= canGoUp;
		g |= canGoDown;
	}
	if (allowDiag)
	{
		if (x > 0 && y > 0 && walkable.get(x - 1, y - 1))
		{
			grid.get(x - 1, y - 1) |= canGoSE;
			g |= canGoNW;
		}
		if (x < width - 1 && y > 0 && walkable.get(x + 1, y - 1))
		{
			grid.get(x + 1, y - 1) |= canGoSW;
			g |= canGoNE;
		}
		if (x > 0 && y < height - 1 && walkable.get(x - 1, y + 1))
		{
			grid.get(x - 1, y + 1) |= canGoNE;
			g |= canGoSW;
		}
		if (x < width - 1 && y < height - 1 && walkable.get(x + 1, y + 1))
		{
			grid.get(x + 1, y + 1) |= canGoNW;
			g |= canGoSE;
		}
	}
}

void PathGrid::closeCell(int x, int y)
{
	walkable.get(x, y) = false;
	grid.get(x, y) = 0;
	if (x > 0)
	{
		grid.get(x - 1, y) &= ~canGoRight;
	}
	if (x < width - 1)
	{
		grid.get(x + 1, y) &= ~canGoLeft;
	}
	if (y > 0)
	{
		grid.get(x, y - 1) &= ~canGoDown;
	}
	if (y < height - 1)
	{
		grid.get(x, y + 1) &= ~canGoUp;
	}
	if (allowDiag)
	{
		if (x > 0 && y > 0)
		{
			grid.get(x - 1, y - 1) &= ~canGoSE;
		}
		if (x < width - 1 && y > 0)
		{
			grid.get(x + 1, y - 1) &= ~canGoSW;
		}
		if (x > 0 && y < height - 1)
		{
			grid.get(x - 1, y + 1) &= ~canGoNE;
		}
		if (x < width - 1 && y < height - 1)
		{
			grid.get(x + 1, y + 1) &= ~canGoNW;
		}
	}
}

void PathGrid::setWalkable(int x, int y, bool val)
{
	walkable.get(x, y) = val;
}

void PathGrid::setWeight(int x, int y, float weight)
{
	weights.get(x, y) = weight;
}

PathGrid::CellType PathGrid::getCell(int x, int y) const
{
	return grid.get(x, y);
}

bool PathGrid::getWalkable(int x, int y) const
{
	return walkable.get(x, y);
}

PathGrid::Node PathGrid::getNodeFromPos(const sf::Vector2f& pos) const
{
	int x = pos.x / cellWidth;
	if (x < 0)
		x = 0;
	if (x >= width)
		x = width - 1;
	int y = pos.y / cellHeight;
	if (y < 0)
		y = 0;
	if (y >= height)
		y = height - 1;
	return Node(*this, x, y);
}

}
