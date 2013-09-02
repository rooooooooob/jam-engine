#ifndef JE_MINMAX_HPP
#define JE_MINMAX_HPP

namespace je
{

template <typename T>
inline T min(T a, T b)
{
	return a < b ? a : b;
}

template <typename T>
inline T max(T a, T b)
{
	return a > b ? a : b;
}

}

#endif
