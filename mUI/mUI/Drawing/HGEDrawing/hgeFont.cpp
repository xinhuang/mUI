#include "hgeFont.h"
#include "PHGE.h"

#include "../../String.h"

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

Font::Font( const String& family_name, float size ) : family_name_(family_name), size_(size), texture_(0)
{
	_Load();

}

const String& Font::get_FontFamily() const
{
	return family_name_;
}

hgeSprite Font::get_Sprite( wchar_t c )
{
	if (texture_ == 0)
		_Load();

	int x = (c & 0xFF) * get_Size();
	int y = (c >> 8) * get_Size();

	float glyph_width = static_cast<float>(y == 0 ? get_Size() / 2 : get_Size());
	float glyph_height = static_cast<float>(get_Size());

	if (texture_ == 0)
		goto __no_found;

	{
		PHGE hge;
		int w = hge->Texture_GetWidth(texture_);
		int h = hge->Texture_GetHeight(texture_);

		float size = static_cast<float>(get_Size());
		if (w > x && h > y)
			return hgeSprite(texture_, static_cast<float>(x), static_cast<float>(y), 
			glyph_width, glyph_height);
	}

__no_found:
	return hgeSprite(0, 0.f, 0.f, glyph_width, glyph_height);
}

void Font::_Load()
{
	String file_name = get_FontFamily();
	file_name += L".png";
	PHGE hge;
	texture_ = hge->Texture_Load(file_name.ToANSI().c_str());
}

int Font::get_Size() const
{
	return static_cast<int>(size_);
}

Font::~Font()
{
	PHGE hge;
	hge->Texture_Free(texture_);
	texture_ = 0;
}

}}}}
