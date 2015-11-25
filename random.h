#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
public:
    Random();
    int RandomInt(int, int);
private:
    std::mt19937 _mt;
};

#endif // RANDOM_H
