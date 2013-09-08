#include "Random.hpp"

namespace
{
// TODO: make these use <random> and be less crap
float randomf(float n)
{
    return ((rand() % 0xFFFF) / (float) 0xFFFF) * n;
}

float random(int n)
{
	return rand() % n;
}

}

