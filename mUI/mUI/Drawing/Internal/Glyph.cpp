#include "Glyph.h"

#include <memory.h>

namespace mUI{ namespace System { namespace Drawing{

Glyph::Glyph( utf32_t code, const argb_t* buffer, 
			 size_t width, size_t height,
			 int x, int y,
			 int adv_x, int adv_y ) :
	code_(code), width_(width), height_(height), 
	x_(x), y_(y), adv_x_(adv_x), adv_y_(adv_y),
	tex_(buffer, width, height)
{
}

Glyph::Glyph( utf32_t code, const int8_t* grey_buffer, 
			 size_t width, size_t height,
			 int x, int y, 
			 int adv_x, int adv_y ) :
	code_(code), width_(width), height_(height), 
	x_(x), y_(y), adv_x_(adv_x), adv_y_(adv_y),
	tex_(grey_buffer, width, height)
{
}

Glyph::~Glyph()
{
}

size_t Glyph::get_Width() const
{
	return width_;
}

size_t Glyph::get_Height() const
{
	return height_;
}

int Glyph::get_AdvanceX() const
{
	return adv_x_ >> 6;
}

int Glyph::get_AdvanceY() const
{
	return adv_y_ >> 6;
}

utf32_t Glyph::get_Code() const
{
	return code_;
}

Texture& Glyph::get_Texture() 
{
	return tex_;
}

const Texture& Glyph::get_Texture() const
{
	return tex_;
}

int Glyph::get_X() const
{
	return x_;
}

int Glyph::get_Y() const
{
	return y_;
}

}}}
