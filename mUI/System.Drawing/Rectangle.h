/*
	Copyright 2011 hello.patz@gmail.com

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "Point.h"
#include "Size.h"

#include <System/System.h>

namespace mUI{ namespace System{  namespace Drawing{

class DRAWING_ENTRY Rectangle
{
public:
	Point Location;
	Size Size;

	Rectangle(const Point& pt, const Drawing::Size& size);
	Rectangle(int x, int y, int w, int h);

	Rectangle& operator+= (const Point& point);
	Rectangle operator+ (const Point& point) const;

	bool Contains(const Point& location) const;

	const Point& get_Location() const { return Location; }
	void set_Location(const Point& value) { Location = value; }

	int get_Top() const { return Location.Y; }

	int get_Bottom() const { return Location.Y + Size.Height; }

	int get_Left() const { return Location.X; }

	int get_Right() const { return Location.X + Size.Width; }
};

}}}

#endif // __RECTANGLE_H__