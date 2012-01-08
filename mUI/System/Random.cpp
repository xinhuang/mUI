#include "Random.h"
#include "BasicType.h"

#include <cstdlib>
#include <ctime>

namespace mUI{ namespace System{

Random::Random() : seed_(static_cast<size_t>(time(null)))
{
}

Random::Random(size_t seed) : seed_(seed)
{
}

Random::~Random()
{
}

int Random::Next()
{
	return (((seed_ = seed_ * 214013L + 2531011L) >> 16) & 0x7fff);
}

int Random::Next( int max_value )
{
	if (max_value == 0)
		return 0;
	return Next() % max_value;
}

int Random::Next( int min_value, int max_value )
{
	return Next(max_value - min_value) + min_value;
}

}}