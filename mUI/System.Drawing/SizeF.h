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

#ifndef __SIZEF_H__
#define __SIZEF_H__

#include <System/System.h>
#include "Size.h"
#include "PointF.h"

namespace mUI{ namespace System{ namespace Drawing{

class DRAWING_ENTRY SizeF
{
public:
	SizeF() : width_(0.f), height_(0.f), empty_(true) {}
	SizeF(float w, float h);

	SizeF(const SizeF& value) { *this = value; }
	SizeF& operator=(const SizeF& value);

	bool get_IsEmpty() const { return empty_; }
	float get_Width() const { return width_; }
	float get_Height() const { return height_; }

	void set_IsEmpty(bool value) { empty_ = value; }
	void set_Width(float value) { width_ = value; }
	void set_Height(float value) { height_ = value; }

	Size ToSize() const;
	PointF ToPointF() const;

	operator PointF() const { return ToPointF(); }
	bool operator==(const SizeF& rhs);
	bool operator!=(const SizeF& rhs) { return false; }
	SizeF& operator+(const SizeF& rhs);
	SizeF& operator-(const SizeF& rhs);


	static const SizeF Empty;

private:
	bool empty_;
	float width_;
	float height_;
};

}}}

#endif // __SIZEF_H__
