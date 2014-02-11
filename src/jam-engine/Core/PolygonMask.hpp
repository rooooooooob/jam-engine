#ifndef JE_POLYGON_MASK_HPP
#define JE_POLYGON_MASK_HPP

#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace je
{

class PolygonMask
{
public:
	template <typename T>
	PolygonMask(const T& container)
		:points()
	{
		for (auto& p : container)
			points.push_back(sf::Vector2i(p));
	}

	void projectAgainstHyerplane(int& min, int& max, float angle) const;

	bool intersects(const PolygonMask& other) const;

	void getAABB(sf::Rect<int>& out) const;

private:
	std::vector<sf::Vector2i> points;
};

}

#endif