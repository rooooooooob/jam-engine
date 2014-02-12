#ifndef JE_POLYGON_MASK_HPP
#define JE_POLYGON_MASK_HPP

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "jam-engine/Core/DetailedMask.hpp"

namespace je
{

class CircleMask;

class PolygonMask : public DetailedMask
{
public:
	template <typename T>
	PolygonMask(const T& container)
		:DetailedMask(Type::Polygon)
		,points()
	{
		//for (auto& p : container)
		//	points.push_back(sf::Vector2i(p));
	}

	void projectAgainstHyerplane(int& min, int& max, float angle) const;

	bool intersects(const DetailedMask& other) const override;

	void getAABB(int& minX, int& maxX, int& minY, int& maxY) const override;

private:
	std::vector<sf::Vector2i> points;

	friend bool intersectsPolygonOnPolygon(const PolygonMask&, const PolygonMask&);
	friend bool intersectsPOlygonOnCircle(const PolygonMask&, const CircleMask&);
};

}

#endif