#include "Rectangle.h"

namespace mUI{ namespace System{  namespace Drawing{

bool mUI::System::Drawing::Rectangle::Contains( const Point& location ) const
{
	if (location.X >= this->Location.X && location.X <= this->Location.X + Size.Width
		&& location.Y >= this->Location.Y && location.Y <= this->Location.Y + Size.Height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rectangle::Rectangle( const Point& pt, const Drawing::Size& size ) : Location(pt), Size(size)
{
}

Rectangle Rectangle::operator+( const Point& point ) const
{
	Rectangle rect = *this;
	rect.Location += point;
	return rect;
}

Drawing::Rectangle& mUI::System::Drawing::Rectangle::operator+=( const Point& point )
{
	Location += point;
	return *this;
}


}}}
