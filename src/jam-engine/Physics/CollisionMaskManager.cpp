#include "jam-engine/Physics/CollisionMaskManager.hpp"

#include "jam-engine/Utility/Assert.hpp"

namespace je
{

CollisionMaskManager::CollisionMaskManager()
	:masks()
{
}

void CollisionMaskManager::add(const std::string& name, DetailedMask::MaskRef& mask)
{
	masks[name] = std::move(mask);
}

DetailedMask::MaskRef CollisionMaskManager::create(const std::string& name) const
{
	auto it = masks.find(name);
	JE_ASSERT_MSG(it != masks.end(), std::string("Attempting to load mask named <" + name + "> but mask with that name doesn't exist.").c_str());
	return it->second->clone();
}

}