#include "FontImpl.h"

#include "FTFont.h"

#ifdef CreateFont
#	undef CreateFont
#endif

namespace mUI{ namespace System{ namespace Drawing{

FontImpl* FontImpl::CreateFont( const String& family_name, float size )
{
	return new FTFont(family_name, size);
	assert("Not implemented!");
	return null;
}

bool FontImpl::Initialize()
{
	return FTFont::Initialize();
}

bool FontImpl::Dispose()
{
	return FTFont::Dispose();
}

}}}
