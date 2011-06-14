#include "SystemInformation.h"

#include "../Drawing/Drawing.h"

namespace mUI{ namespace System{  namespace Forms{

using Drawing::Size;

int SystemInformation::GetCaptionHeight()
{
	return 26;
}

const Size& SystemInformation::GetCaptionButtonSize()
{
	static const Size caption_button_size(21, 21);
	return caption_button_size;
}

}}}
