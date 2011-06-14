#include "Frame.h"

namespace mUI{ namespace System{  namespace Forms{

Frame::Frame()
{
	set_FormBorderStyle(FormBorderStyle::None);
}

int Frame::get_Fps() const
{
	return 30;
}

bool Frame::LogicTick( float delta )
{
	return false;
}

}}}
