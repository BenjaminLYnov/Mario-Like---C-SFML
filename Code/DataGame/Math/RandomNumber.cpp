#include "RandomNumber.hpp"
#include <random>

int RandomNumber::RandomInt(int min, int max)
{
    int nRand;
    nRand = min + (int)((float)rand() * ( max - min + 1) / (RAND_MAX - 1));
    return nRand;
}

float RandomNumber::RandomFloat(float min, float max)
{
    float nRand;
    nRand = min + (rand() * ( max - min + 1) / (RAND_MAX - 1));
    return nRand;
}
