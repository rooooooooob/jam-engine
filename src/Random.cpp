#include "Random.hpp"

namespace je
{
// TODO: make these use <random> and be less crap
float randomf(float n)
{
    return ((rand() % 0xFFFF) / (float) 0xFFFF) * n;
}

int random(int n)
{
	return rand() % n;
}

}

