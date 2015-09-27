#ifndef JE_REF_HPP
#define JE_REF_HPP

#include <memory>

#include "jam-engine/Core/Entity.hpp"

namespace je
{

template <typename EntityType>
class Ref
{
public:
	Ref();

	Ref(EntityType& entity);

	Ref(const Ref<Entity>& copy);

	EntityType& operator*() const;

	EntityType* operator->() const;

	explicit operator bool() const;

	bool operator==(std::nullptr_t) const;

	bool operator!=(std::nullptr_t) const;

	template <typename RHSType>
	bool operator==(const Ref<RHSType>& rhs) const;

	template <typename RHSType>
	bool operator!=(const Ref<RHSType>&rhs) const;

	operator EntityType*() const;

	Ref<EntityType>& operator=(const Ref<Entity>& rhs);

	Ref<EntityType>& operator=(std::nullptr_t);

//private:

	EntityType *entity;

	std::shared_ptr<bool> isAlive;

	//template <typename OtherType>
	//friend class Ref<OtherType>; // this is dumb
};

template <typename EntityType>
Ref<EntityType>::Ref()
	:entity(nullptr)
	,isAlive(new bool(false))
{
}


template <typename EntityType>
Ref<EntityType>::Ref(EntityType& entity)
	:entity(&entity)
	,isAlive(entity.aliveRef())
{
}


template <typename EntityType>
Ref<EntityType>::Ref(const Ref<Entity>& copy)
	:entity(static_cast<EntityType*>(copy.entity))
	,isAlive(copy.isAlive)
{
}

template <typename EntityType>
EntityType& Ref<EntityType>::operator*() const
{
	return *entity;
}


template <typename EntityType>
EntityType* Ref<EntityType>::operator->() const
{
	return *isAlive ? entity : nullptr;
}


template <typename EntityType>
Ref<EntityType>::operator bool() const
{
	return *isAlive;
}


template <typename EntityType>
bool Ref<EntityType>::operator==(std::nullptr_t) const
{
	return !*isAlive;
}


template <typename EntityType>
bool Ref<EntityType>::operator!=(std::nullptr_t) const
{
	return *isAlive;
}


template <typename EntityType>
template <typename RHSType>
bool Ref<EntityType>::operator==(const Ref<RHSType>& rhs) const
{
	return (!*isAlive && !*rhs.isAlive) || (*isAlive && *rhs.isAlive && entity == rhs.entity);
}


template <typename EntityType>
template <typename RHSType>
bool Ref<EntityType>::operator!=(const Ref<RHSType>&rhs) const
{
	return (*isAlive != *rhs.isAlive) || (*isAlive && *rhs.isAlive && entity != rhs.entity);
}

template <typename EntityType>
Ref<EntityType>::operator EntityType*() const
{
	return *isAlive ? entity : nullptr;
}

template <typename EntityType>
Ref<EntityType>& Ref<EntityType>::operator=(const Ref<Entity>& rhs)
{
	entity = static_cast<EntityType*>(rhs.entity);
	isAlive = rhs.isAlive;
	return *this;
}

template <typename EntityType>
Ref<EntityType>& Ref<EntityType>::operator=(std::nullptr_t)
{
	if (entity)
	{
		entity = nullptr;
		isAlive.reset(new bool(false));
	}
	return *this;
}

} // je

#endif // JE_REF_HPP