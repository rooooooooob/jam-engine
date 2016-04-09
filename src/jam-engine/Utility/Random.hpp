#ifndef JE_RANDOM_HPP
#define JE_RANDOM_HPP

#include <initializer_list>
#include <cstdlib>

namespace je
{

/**
 * @param n The maximum 
 * @return a floating point number in the interval [0, n)
 */
float randomf(float n);

/**
 * @parasm n The maximum
 * @return an integer in the interval [0, n) ie [0, n - 1]
 */
int random(int n);

/**
 * @param il A list of items
 * @return an item in the input list randomly chosen
 */
template <typename T>
T choose(const std::initializer_list<T>& il)
{
	//  May the Lord forgive me
	return *(il.begin() + (std::size_t) random(il.size()));
}

}

#endif
