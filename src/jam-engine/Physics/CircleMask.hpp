#ifndef JE_CIRCLEMASK_HPP
#define JE_CIRCLEMASK_HPP

#ifdef JE_DEBUG
	#include <SFML/Graphics/RenderTarget.hpp>
	#include <SFML/Graphics/CircleShape.hpp>
#endif

#include "jam-engine/Physics/DetailedMask.hpp"

namespace je
{

class PolygonMask;

class CircleMask : public DetailedMask
{
public:
	CircleMask(float radius);

	const sf::Transformable& getBaseTransform() const;

	sf::Transformable& getBaseTransform();

	float getRadius() const;

	const sf::Vector2f& getPos() const;

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
	sf::Vector2f center;
	float radius;
	float originalRadius;
	sf::Transformable baseTransform;
#ifdef JE_DEBUG
	sf::CircleShape debugCircle;
#endif


	friend bool intersectsCircleOnCircle(const PolygonMask&, const PolygonMask&);
	friend bool intersectsPolygonOnCircle(const PolygonMask&, const CircleMask&);
};

} // je

#endif
