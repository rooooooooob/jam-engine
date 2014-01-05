#ifndef JE_PATHFIND_HPP

#include <forward_list>
#include <set>
#include <map>
#include <queue>
#include <SFML/System/Vector2.hpp>

namespace je
{


//	to support stuff with push_front() (default)
template <typename R, typename N, typename P>
void reconstructPath(R& results, N node, const N& start, const P& prev)
{
	do
	{
		results.push_front(node.getPos());
		node = prev[node];
	}
	while (node != start);
}

//	to support stuff with push_back()
template <typename R, typename N, typename P>
void reconstructPathPushBack(R& results, N node, const N& start, const P& prev)
{
	std::forward_list<sf::Vector2f> path;
	do
	{
		path.push_front(node.getPos());
		node = prev[node];
	}
	while (node != start);
	for (const sf::Vector2f& pos : path)
		results.push_back(pos);
}

template <typename N, typename P>
void reconstructPath(std::vector<sf::Vector2f>& results, N node, const N& start, const P& prev)
{
	reconstructPathPushBack(results, node, start, prev);
}


template <typename R, typename G, typename D>
void findSinglePath(R& results, G& graph, const sf::Vector2f& source, const D& destinations)
{
}

template <typename R, typename G, typename D>
void findSinglePathUnweighted(R& results, G& graph, const sf::Vector2f& source, const D& destinations)
{
	std::map<typename G::ID, bool> visited;
	std::map<typename G::Node, typename G::ID> prev;
	std::queue<typename G::Node> visitQueue;

	std::set<typename G::ID> destIDs;
	for (const sf::Vector2f& pos : destinations)
		destIDs.insert(graph.getNodeFromPos(pos).getID());

	typename G::Node start = graph.getNodeFromPos(source);
	visited[start.getID()] = true;
	visitQueue.push(start);

	typename G::Node v = start;

	while (!visitQueue.empty())
	{
		v = visitQueue.front();

		if (destIDs.count(v))
		{
			reconstructPath(results, v, start, prev);
			break;
		}

		visitQueue.pop();

		v.getNeighbors(visitQueue,
			[&prev,&v](decltype(visitQueue)& q, typename G::Node n)
			{
				q.push(n);
				prev[n] = v;
			},
			[&visited](typename G::ID id) -> bool
			{
				//	optimize when you get internet and see std::map::insert's doc
				bool ret = visited.count(id);
				visited[id] = true;
				return ret;
			}
		);
	}
}


}

#endif
