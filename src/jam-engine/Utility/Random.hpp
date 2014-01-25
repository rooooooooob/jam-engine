#ifndef JE_RANDOM_HPP
#define JE_RANDOM_HPP

#include <initializer_list>
#include <cstdlib>

namespace je
{

float randomf(float n);

int random(int n);

template <typename T>
T choose(const std::initializer_list<T>& il)
{
	//  May the Lord forgive me
	return *(il.begin() + (std::size_t) randomf(il.size()));
}

}

#endif
