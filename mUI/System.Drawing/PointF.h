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

#ifndef __PointF_H__
#define __PointF_H__

#include "Export.h"

namespace mUI{ namespace System{  namespace Drawing{

class DRAWING_ENTRY PointF
{
public:
	PointF() : X(0), Y(0) {}
	PointF(float x, float y) : X(x), Y(y)
	{}

	PointF& operator +=(const PointF& rhs)
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}
	PointF operator +(const PointF& rhs) const
	{
		return PointF(X + rhs.X, Y + rhs.Y);
	}

	PointF& operator -=(const PointF& rhs)
	{
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}
	PointF operator -(const PointF& rhs) const
	{
		return PointF(X - rhs.X, Y - rhs.Y);
	}

	bool operator==(const PointF& rhs) const
	{
		if (this == &rhs)
			return true;
		else
			return X == rhs.X && Y == rhs.Y;
	}

	bool operator!=(const PointF& rhs) const
	{
		return !(*this == rhs);
	}

	float X;
	float Y;

	static const PointF Empty;
};

}}}

#endif // __PointF_H__