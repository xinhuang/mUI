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

#ifndef __POINT_H__
#define __POINT_H__

#include "../mUIBase.h"

namespace mUI{ namespace System{  namespace Drawing{

class MUI_ENTRY Point
{
public:
	Point() : X(0), Y(0) {}
	Point(int x, int y) : X(x), Y(y)
	{}

	Point& operator +=(const Point& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}
	Point operator +(const Point& rhs) const
	{
		return Point(X + rhs.X, Y + rhs.Y);
	}

	Point& operator -=(const Point& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}
	Point operator -(const Point& rhs) const
	{
		return Point(X - rhs.X, Y - rhs.Y);
	}

	bool operator==(const Point& rhs) const
	{
		if (this == &rhs)
			return true;
		else
			return X == rhs.X && Y == rhs.Y;
	}

	bool operator!=(const Point& rhs) const
	{
		return !(*this == rhs);
	}

	int X;
	int Y;

	static const Point Empty;
};

}}}

#endif // __POINT_H__