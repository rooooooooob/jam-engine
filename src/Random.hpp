#ifndef JE_RANDOM_HPP
#define JE_RANDOM_HPP

#include <initializer_list>
#include <cstdlib>

namespace je
{

template <typename T>
T choose(const std::initializer_list<T>& il)
{
    //  May the Lord forgive me
    return *(il.begin() + (std::size_t) randomf(il.size()));
}

float randomf(float n);

int random(int n);

}

#endif
