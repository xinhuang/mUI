#include "SolidBrush.h"

namespace mUI{ namespace System{  namespace Drawing{

SolidBrush::SolidBrush( const Color& color ) : Brush(Brush::Solid), color_(color)
{

}

const Color& SolidBrush::get_Color() const
{
	return color_;
}

Color& SolidBrush::get_Color()
{
	return color_;
}

void SolidBrush::set_Color( const Color& color )
{
	color_ = color;
}

}}}