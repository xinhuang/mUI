#include "IFont.h"
#include "HGEDrawing/hgeFont.h"

#ifdef CreateFont
#	undef CreateFont
#endif

namespace mUI{ namespace System{ namespace Drawing{

IFont* IFont::CreateFont( const String& family_name, float size )
{
	return new HGEDrawing::Font(family_name, size);
}

}}}
