#ifndef JE_DETAILED_MASK_HPP
#define JE_DETAILED_MASK_HPP

#include <memory>

#ifdef JE_DEBUG
	#include <SFML/Graphics/RenderTarget.hpp>
#endif
#include <SFML/Graphics/Transform.hpp>

namespace je
{

class DetailedMask
{
public:
	typedef std::unique_ptr<DetailedMask> MaskRef;
	enum class Type
	{
		Polygon,
		Circle,
		Pixel
	};


	virtual ~DetailedMask()
	{
	}

	virtual bool intersects(const DetailedMask& other) const = 0;

	virtual void getAABB(int& minX, int& maxX, int& minY, int& maxY) const = 0;

	virtual void updateTransform(const sf::Transform& transform) = 0;

	virtual MaskRef clone() const = 0;

#ifdef JE_DEBUG
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual void setColor(sf::Color color) = 0;
#endif

	const Type type;
protected:

	DetailedMask(Type type)
		:type(type)
	{
	}
};

}

#endif