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
	static const CellType canGoNW;
	static const CellType canGoNE;
	static const CellType canGoSW;
	static const CellType canGoSE;
	
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
	
	PathGrid(int cellWidth, int cellHeight, int width, int height, bool allowDiag = true, float diagRatio = 1.4142135);
	
	void addPath(int x, int y, CellType type);
	
	void removePath(int x, int y, CellType type);
	
	void addAllPaths();
	
	void removeAllPaths();
	
	void openCell(int x, int y);
	
	void closeCell(int x, int y);
	
	void setWeight(int x, int y, float weight);
	
	CellType getCell(int x, int y) const;
	
	
private:
	
	int cellWidth, cellHeight;
	int width, height;
	Grid<CellType> grid;
	Grid<float> weights;
	bool allowDiag;
	float diagRatio;
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
	if (allowDiag)
	{
		if (x > 0 && y > 0 && (owner.grid.get(x, y) & canGoNW))
		{
			Node(owner, x - 1, y - 1) NWNode;
			if (!visitedFunc(NWNode.getID()))
				pushFunc(container, NWNode);
		}
		if (x < owner.width - 1 && y > 0 && (owner.grid.get(x, y) & canGoNE))
		{
			Node(owner, x + 1, y - 1) NENode;
			if (!visitedFunc(NENode.getID()))
				pushFunc(container, NENode);
		}
		if (x > 0 && y < height - 1 && (owner.grid.get(x, y) & canGoSW))
		{
			Node(owner, x - 1, y + 1) SWNode;
			if (!visitedFunc(SWNode.getID()))
				pushFunc(container, SWNode);
		}
		if (x < owner.width - 1 && y < owner.height - 1 && (owner.grid.get(x, y) & canGoSE))
		{
			Node(owner, x + 1, y + 1) SENode;
			if (!visitedFunc(SENode.getID()))
				F(container, SENode);
		}
	}
}

}

#endif