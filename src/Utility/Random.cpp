#include "Utility/Random.hpp"

namespace je
{
// TODO: make these use <random> and be less crap
float randomf(float n)
{
	return n ? ((rand() % 0xFFFF) / (float) 0xFFFF) * n : 0;
}

int random(int n)
{
	return n ? rand() % n : 0;
}

}

