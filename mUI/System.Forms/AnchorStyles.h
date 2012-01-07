#ifndef __MUI_SYSTEM_FORMS_ANCHORSTYLES_H__
#define __MUI_SYSTEM_FORMS_ANCHORSTYLES_H__

namespace mUI{ namespace System{  namespace Forms{

namespace AnchorStyles
{
	enum Enum
	{
		None	= 0x00,
		Top		= 0x01,
		Bottom	= 0x02,
		Left	= 0x04,
		Right	= 0x08,

		TopBottom	= Top | Bottom,
		LeftRight	= Left | Right,
		All			= TopBottom | LeftRight,
	};
}

}}}

#endif
