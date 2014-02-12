#ifndef JE_DETAILED_MASK_HPP
#define JE_DETAILED_MASK_HPP

namespace je
{

class DetailedMask
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


	const Type type;
protected:

	DetailedMask(Type type)
		:type(type)
	{
	}
};

}

#endif