#include "HgeContext.h"

namespace mUI{ namespace Extra{

struct HgeContext::Data
{
	Size windowSize;
};

HgeContext::HgeContext()
	: _d(new Data())
{
	_d->windowSize = Size(400, 300);
}

HgeContext::~HgeContext()
{
	delete _d;
}

const Size HgeContext::get_Size() const
{
	return _d->windowSize;
}

void HgeContext::set_Size(const Size& size)
{
	_d->windowSize = size;
}

}}
