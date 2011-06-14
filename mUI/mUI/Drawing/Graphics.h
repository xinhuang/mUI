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

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "../mUIBase.h"

namespace mUI{ namespace System{
	class String;
}}

namespace mUI{ namespace System{  namespace Drawing{

class Brush;
class Font;
class Image;
class Rectangle;
class Pen;
class Point;
class PointF;

class MUI_ENTRY Graphics
{
public:
	virtual ~Graphics() {}

	virtual void DrawLine(Pen& pen, const Point& pt1, const Point& pt2) = 0;
	virtual void DrawLine(Pen& pen, int X1, int Y1, int X2, int Y2) = 0;

	virtual void FillRectangle(Brush& brush, const Rectangle& rect) = 0;
	virtual void FillRectangle(Brush& brush, int X, int Y, int Width, int Height) = 0;

	virtual void DrawRectangle(Pen& pen, const Rectangle& rect) = 0;
	virtual void DrawRectangle(Pen& pen, int X, int Y, int Width, int Height) = 0;

	virtual void DrawImage(const Image& image, Point pt) = 0;
	virtual void DrawImage(const Image& image, const Rectangle& rect) = 0;
	virtual void DrawImage(const Image& image, int X, int Y, int Width, int Height) = 0;

	virtual void SetClip(const Rectangle& rect) = 0;
	virtual void SetClip(int X, int Y, int Width, int Height) = 0;

	virtual void DrawString(const String& s, Font& font, Brush& brush, const PointF& pt) = 0;
};

}}}

#endif // __GRAPHICS_H__
