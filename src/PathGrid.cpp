#include "PathGrid.hpp"

namespace je
{

const PathGrid::CellType canGoLeft  = 1;
const PathGrid::CellType canGoRight = 2;
const PathGrid::CellType canGoUp    = 4;
const PathGrid::CellType canGoDown  = 8;
const PathGrid::CellType canGoNW    = 16;
const PathGrid::CellType canGoNS    = 32;
const PathGrid::CellType canGoSW    = 64;
const PathGrid::CellType canGoSE    = 128;

/*			PathGrid::Node			*/
PathGrid::Node::Node(const PathGrid& owner, int x, int y)
	:owner(owner)
	,x(x)
	,y(y)
{
}

int PathGrid:Node::getID() const
{
	return (x << 16) + y;
}


/*			PathGrid				*/
PathGrid::PathGrid(int cellWidth, int cellHeight, int width, int height, bool allowDiag, float diagRatio)
	:cellWidth(cellWidth)
	,cellHeight(cellHeight)
	,width(width)
	,height(height)
	,grid(width, height)
	,weights(width, height)
	,allowDiag(allowDiag)
	,diagRatio(diagRatio)
{
	for (CellType& type : grid)
		type = 0xFF;	//	allow all paths
	for (float& weight : weights)
		weight = 1.f;
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

void PathGrid::openCell(int x int y)
{
	Grid& g = grid.get(x, y);
	if (x > 0)
	{
		grid.get(x - 1, y) |= canGoRight;
		g |= canGoLeft;
	}
	if (x < width - 1)
	{
		grid.get(x + 1, y) |= canGoLeft;
		g |= canGoRight;
	}
	if (y > 0)
	{
		grid.get(x, y - 1) |= canGoDown;
		g |= canGoUp;
	}
	if (y < height - 1)
	{
		grid.get(x, y + 1) |= canGoUp;
		g |= canGoDown;
	}
	if (allowDiag)
	{
		if (x > 0 && y > 0)
		{
			grid.get(x - 1, y - 1) |= canGoSE;
			g |= canGoNW;
		}
		if (x < width - 1 && y > 0)
		{
			grid.get(x + 1, y - 1) |= canGoSW;
			g |= canGoNE;
		}
		if (x > 0 && y < height - 1)
		{
			grid.get(x - 1, y + 1) |= canGoNE;
			g |= canGoSW;
		}
		if (x < width - 1 && y < height - 1)
		{
			grid.get(x + 1, y + 1) |= canGoNW;
			g |= canGoSE;
		}
	}
}

void PathGrid::closeCell(int x, int y)
{
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

void setWeight(int x, int y, float weight)
{
	weights.get(x, y) = weight;
}

PathGrid::CellType PathGrid::getCell(int x, int y) const
{
	return grid.get(x, y);
}

}