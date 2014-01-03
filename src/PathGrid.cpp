#include "PathGrid.hpp"

namespace je
{

const PathGrid::CellType canGoLeft  = 1;
const PathGrid::CellType canGoRight = 2;
const PathGrid::CellType canGoUp    = 4;
const PathGrid::CellType canGoDown  = 8;

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
PathGrid::PathGrid(int cellWidth, int cellHeight, int width, int height)
	:cellWidth(cellWidth)
	,cellHeight(cellHeight)
	,width(width)
	,height(height)
	,grid(width, height)
{
}

void PathGrid::addPath(int x, int y, CellType type)
{
	grid.get(x, y) |= type;
}

void PathGrid::removePath(int x, int y, CellType type)
{
	grid.get(x, y) &= ~type;
}

}