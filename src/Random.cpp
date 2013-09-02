#include "Random.hpp"

namespace ggj
{

float randomf(float n)
{
    return ((rand() % 0xFFFF) / (float) 0xFFFF) * n;
}

}

