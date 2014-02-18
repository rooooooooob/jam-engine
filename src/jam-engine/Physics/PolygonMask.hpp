#ifndef JE_POLYGON_MASK_HPP
#define JE_POLYGON_MASK_HPP

#include <vector>

#ifdef JE_DEBUG
	#include <SFML/Graphics/RenderTarget.hpp>
	#include <SFML/Graphics/VertexArray.hpp>
#endif
#include <SFML/System/Vector2.hpp>

#include "jam-engine/Physics/DetailedMask.hpp"
#include <initializer_list>
namespace je
{

class CircleMask;

class PolygonMask : public DetailedMask
{
public:
	PolygonMask(const std::initializer_list<sf::Vector2f>& container)
		:DetailedMask(Type::Polygon)
		,points()
		,pointsOriginal()
#ifdef JE_DEBUG
		,debugDrawPoints(sf::PrimitiveType::LinesStrip)
#endif
	{
		for (const auto& p : container)
		{
			points.push_back(sf::Vector2f(p));
			pointsOriginal.push_back(sf::Vector2f(p));
#ifdef JE_DEBUG
			debugDrawPoints.append(sf::Vertex(sf::Vector2f(p), sf::Color::Blue));
#endif
		}
		debugDrawPoints.append(debugDrawPoints[0]);
	}

	PolygonMask(int width, int height);

	PolygonMask(const PolygonMask& other);

	void projectAgainstHyerplane(double& min, double& max, double angle) const;

	bool intersects(const DetailedMask& other) const override;

	void getAABB(int& minX, int& maxX, int& minY, int& maxY) const override;

	void updateTransform(const sf::Transform& transform) override;

	DetailedMask::MaskRef clone() const override;

#ifdef JE_DEBUG
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setColor(sf::Color color) override;
#endif

private:
	std::vector<sf::Vector2f> points;
	std::vector<sf::Vector2f> pointsOriginal;
#ifdef JE_DEBUG
	sf::VertexArray debugDrawPoints;
#endif

	friend bool intersectsPolygonOnPolygon(const PolygonMask&, const PolygonMask&);
	friend bool intersectsPOlygonOnCircle(const PolygonMask&, const CircleMask&);
};

}

#endif