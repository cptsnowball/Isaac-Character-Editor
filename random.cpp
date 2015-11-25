#include "random.h"
#include <ctime>

Random::Random()
{
    this->_mt.seed(time(0));
}

int Random::RandomInt(int min, int max)
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(this->_mt);
}
