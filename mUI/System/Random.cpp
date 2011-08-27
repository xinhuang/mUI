#include "Random.h"

#include <cstdlib>

namespace mUI{ namespace System{

class Random::Impl
{
public:
	Impl() : seed(rand()) {}
	size_t seed;
};

Random::Random() : impl_(new Random::Impl)
{

}

Random::~Random()
{
	delete impl_;
	impl_ = NULL;
}

int Random::Next()
{
	return (((impl_->seed = impl_->seed * 214013L + 2531011L) >> 16) & 0x7fff);
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