#ifndef JE_PATHGRID_HPP
#define JE_PATHGRID_HPP

#include <
#include "Grid.hpp"

namespace js
{

class PathGrid
{
public:
	typedef uint8_t CellType;
	
	static const CellType canGoLeft;
	static const CellType canGoRight;
	static const CellType canGoUp;
	static const CellType canGoDown;
	
	class Node
	{
	public:
		Node(const PathGrid& owner, int x, int y);
		
		template <typename T, typename F, typename V>
		void getNeighbors(T& container, F pushFunc, V visitedFunc);
		
		int getID() const;
		
	private:
		const PathGrid& owner;
		int x, y;
	};
	
	friend class PathGrid::Node;
	
	PathGrid(int cellWidth, int cellHeight, int width, int height);
	
	void addPath(int x, int y, CellType type);
	
	void removePath(int x, int y, CellType type);
	
	
private:
	
	int cellWidth, cellHeight;
	int width, height;
	Grid<CellType> grid;
};

template <typename T, typename F, typename V>
void PathGrid::Node::getNeighbors(T& container, F pushFunc, V visitedFunc)
{
	if (x > 0 && (owner.grid.get(x, y) & canGoLeft))
	{
		Node(owner, x - 1, y) leftNode;
		if (!visitedFunc(leftNode.getID()))
			pushFunc(container, leftNode);
	}
	if (x < owner.width - 1 && (owner.grid.get(x, y) & canGoRight))
	{
		Node(owner, x + 1, y) rightNode;
		if (!visitedFunc(rightNode.getID()))
			pushFunc(container, rightNode);
	if (y > 0 && (owner.grid.get(x, y) & canGoUp))
	{
		Node(owner, x, y - 1) upNode;
		if (!visitedFunc(upNode.getID()))
			pushFunc(container, upNode);
	}
	if (y < owner.height - 1 && (owner.grid.get(x, y) & canGoDown))
	{
		Node(owner, x, y + 1) downNode;
		if (!visitedFunc(downNode.getID()))
			F(container, downNode);
	}
}

}

#endif