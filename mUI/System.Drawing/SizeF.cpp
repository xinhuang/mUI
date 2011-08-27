#include "SizeF.h"

namespace mUI{ namespace System{ namespace Drawing{

const SizeF SizeF::Empty;

SizeF::SizeF( float w, float h ) : width_(w), height_(h)
{
	if (fequ(w, 0.f) && fequ(h, 0.f))
		set_IsEmpty(true);
	else
		set_IsEmpty(false);
}

SizeF& SizeF::operator=( const SizeF& value )
{
	set_IsEmpty(value.get_IsEmpty());
	set_Width(value.get_Width());
	set_Height(value.get_Height());
	return *this;
}

bool SizeF::operator==( const SizeF& rhs )
{
	if (get_IsEmpty() && rhs.get_IsEmpty())
		return true;
	else
		return fequ(get_Width(), rhs.get_Width())
		&& fequ(get_Height(), rhs.get_Height());
}

Drawing::Size SizeF::ToSize() const
{
	return Size(static_cast<int>(get_Width()), static_cast<int>(get_Height()));
}

PointF SizeF::ToPointF() const
{
	return PointF(get_Width(), get_Height());
}

SizeF& SizeF::operator+( const SizeF& rhs )
{
	set_Width(get_Width() + rhs.get_Width());
	set_Height(get_Height() + rhs.get_Height());
	return *this;
}

SizeF& SizeF::operator-( const SizeF& rhs )
{
	set_Width(get_Width() - rhs.get_Width());
	set_Height(get_Height() - rhs.get_Height());
	return *this;
}

}}}
