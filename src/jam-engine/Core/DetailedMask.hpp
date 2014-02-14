#ifndef JE_DETAILED_MASK_HPP
#define JE_DETAILED_MASK_HPP

#include <SFML/Graphics/Transformable.hpp>
#ifdef JE_DEBUG
	#include <SFML/Graphics/RenderTarget.hpp>
#endif
namespace je
{

class DetailedMask : public sf::Transformable
{
public:
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

	virtual void updateTransforms() = 0;

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