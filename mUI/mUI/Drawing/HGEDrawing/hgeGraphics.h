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

#ifndef __HGE_GRAPHICS_H__
#define __HGE_GRAPHICS_H__

#include "../Graphics.h"
#include "../Point.h"
#include "PHGE.h"

namespace mUI{ namespace System{
	class String;
}}

namespace mUI{ namespace System{  namespace Drawing{
	class Brush;
	class SolidBrush;
	class Font;
	class Pen;
	class PointF;
	class Rectangle;
	class Size;
}}}

using namespace mUI::System;
using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

class Graphics :
	public Drawing::Graphics
{
public:
	Graphics(const Rectangle& clip_rect);
	virtual ~Graphics();

	virtual void DrawLine(Pen& pen, const Point& pt1, const Point& pt2);
	virtual void DrawLine(Pen& pen, int X1, int Y1, int X2, int Y2);
	virtual void DrawLine(Pen& pen, float X1, float Y1, float X2, float Y2);

	virtual void FillRectangle(Brush& brush, const Rectangle& rect);
	virtual void FillRectangle(Brush& brush, int x, int y, int width, int height);

	virtual void DrawRectangle(Pen& pen, const Rectangle& rect);
	virtual void DrawRectangle(Pen& pen, int X, int Y, int Width, int Height);

	virtual void DrawImage(const Drawing::Image& image, Point pt);
	virtual void DrawImage(const Drawing::Image& image, const Rectangle& rect);
	virtual void DrawImage(const Image& image, int X, int Y, int Width, int Height);

	virtual void SetClip(const Rectangle& rect);
	virtual void SetClip(int X, int Y, int Width, int Height);

	virtual void DrawString(const String& s, Drawing::Font& font, Brush& brush, const PointF& pt);

protected:
	void FillRectangle(SolidBrush& brush, const Rectangle& rect);
	void FillRectangle(SolidBrush& brush, int X, int Y, int Width, int Height);

	void DrawString(const String& s, Drawing::Font& font, SolidBrush& brush, const PointF& pt);

private:
	bool enabled_;				// If the clipping is so small that we ignore the request.
	PHGE hge_;
	Point offset_;

	static const float UI_Z;
};

}}}}

#endif // __HGE_GRAPHICS_H__
