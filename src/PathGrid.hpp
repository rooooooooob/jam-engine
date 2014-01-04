#ifndef JE_PATHGRID_HPP
#define JE_PATHGRID_HPP

#include <cstdint>
#include "Grid.hpp"

namespace je
{

void update();

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

		/**
		 * Pushes all unvisited neighbors of Node into the given container using the provided functions
		 * @param container The queue to push into
		 * @param pushFunc The function to push the Node into the container. Type: (decltype(container)&, Node)->void
		 * @param visitedFunc A function that marks a Node as visited and returns true if it wasn't before. Type: (int)->void
		 */
		template <typename T, typename F, typename V>
		void getNeighbors(T& container, F pushFunc, V visitedFunc);

		/**
		 * Creates a UNIQUE id for each Node (It is only unique vs othe Nodes in this Grid)
		 * @return the ID
		 */
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

	/**
	 * Marks a cell of the Grid as reachable from all surrounding cells as well as letting
	 * you get to all neighbors from this cell if those neighbors are walkable
	 * @param x The X position
	 * @Param y The Y position
	 */
	void openCell(int x, int y);

	/**
	 * Marks the cell unreachable from all walkable neighbors
	 * @param x The X position
	 * @param y The Y position
	 */
	void closeCell(int x, int y);

	/**
	 * Marks a cell in the graph as walkable
	 */
	void setWalkable(int x, int y, bool val);

	void setWeight(int x, int y, float weight);

	CellType getCell(int x, int y) const;

	bool getWalkable(int x, int y) const;

private:

	int cellWidth, cellHeight;
	int width, height;
	Grid<CellType> grid;
	Grid<float> weights;
	Grid<bool> walkable;
	bool allowDiag;
	float diagRatio;
};

template <typename T, typename F, typename V>
void PathGrid::Node::getNeighbors(T& container, F pushFunc, V visitedFunc)
{
	if (x > 0 && walkable.get(x - 1, y) && (owner.grid.get(x, y) & canGoLeft))
	{
		Node leftNode(owner, x - 1, y);
		if (!visitedFunc(leftNode.getID()))
			pushFunc(container, leftNode);
	}
	if (x < owner.width - 1 && walkable.get(x + 1, y) && (owner.grid.get(x, y) & canGoRight))
	{
		Node rightNode(owner, x + 1, y);
		if (!visitedFunc(rightNode.getID()))
			pushFunc(container, rightNode);
	}
	if (y > 0 && walkable.get(x, y - 1) && (owner.grid.get(x, y) & canGoUp))
	{
		Node upNode(owner, x, y - 1);
		if (!visitedFunc(upNode.getID()))
			pushFunc(container, upNode);
	}
	if (y < owner.height - 1 && walkable.get(x, y + 1) && (owner.grid.get(x, y) & canGoDown))
	{
		Node downNode(owner, x, y + 1);
		if (!visitedFunc(downNode.getID()))
			pushFunc(container, downNode);
	}
	if (allowDiag)
	{
		if (x > 0 && y > 0 && walkable.get(x - 1, y - 1) && (owner.grid.get(x, y) & canGoNW))
		{
			Node NWNode(owner, x - 1, y - 1);
			if (!visitedFunc(NWNode.getID()))
				pushFunc(container, NWNode);
		}
		if (x < owner.width - 1 && walkable.get(x + 1, y - 1) && y > 0 && (owner.grid.get(x, y) & canGoNE))
		{
			Node NENode(owner, x + 1, y - 1);
			if (!visitedFunc(NENode.getID()))
				pushFunc(container, NENode);
		}
		if (x > 0 && y < height - 1 && walkable.get(x - 1, y + 1) && (owner.grid.get(x, y) & canGoSW))
		{
			Node SWNode(owner, x - 1, y + 1);
			if (!visitedFunc(SWNode.getID()))
				pushFunc(container, SWNode);
		}
		if (x < owner.width - 1 && y < owner.height - 1 && walkable.get(x + 1, y + 1) && (owner.grid.get(x, y) & canGoSE))
		{
			Node SENode(owner, x + 1, y + 1);
			if (!visitedFunc(SENode.getID()))
				pushFunc(container, SENode);
		}
	}
}

}

#endif
