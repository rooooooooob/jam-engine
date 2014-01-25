#ifndef JE_MATH_HPP
#define JE_MATH_HPP

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

template <typename T>
inline T abs(T n)
{
	return n > 0 ? n : -n;
}

template <typename T, typename L>
void limit(T& n, const L& upper)
{
	if (n > upper)
		n = upper;
}

template <typename T, typename L>
void limit(T& n, const L& lower, const L& upper)
{
	if (n > upper)
		n = upper;
	else if (n < lower)
		n = lower;
}

}

#endif
