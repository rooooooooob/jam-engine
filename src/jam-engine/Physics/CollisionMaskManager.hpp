#ifndef JE_COLLISION_MASK_MANAGER_HPP
#define JE_COLLISION_MASK_MANAGER_HPP

#include <map>
#include <memory>
#include <string>

#include "jam-engine/Physics/DetailedMask.hpp"

namespace je
{

class DetailedMask;

class CollisionMaskManager
{
public:
	CollisionMaskManager();

	void add(const std::string& name, DetailedMask::MaskRef& mask);

	DetailedMask::MaskRef create(const std::string& name) const;

private:

	std::map<std::string, DetailedMask::MaskRef> masks;
};

}

#endif