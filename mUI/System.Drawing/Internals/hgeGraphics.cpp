#include "hgeGraphics.h"

#include "PHGE.h"

#include "../Point.h"
#include "../PointF.h"
#include "../Rectangle.h"
#include "../Pen.h"
#include "../SolidBrush.h"
#include "../Image.h"
#include "../Font.h"
#include "../Internals/Glyph.h"
#include "../Internals/FontImpl.h"

#include <hgesprite.h>
#include "hgefont.h"

// warning C4244: '=' : conversion from 'int' to 'float', possible loss of data
#pragma warning(disable: 4244)

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

const float Graphics::UI_Z = 0.5f;

Graphics::Graphics(const Rectangle& clip_rect) : offset_(clip_rect.Location), enabled_(true)
{
	SetClip(mUI::System::Drawing::Rectangle(Point::Empty, clip_rect.Size));
}

Graphics::~Graphics()
{
}

void Graphics::DrawLine( Pen& pen, const Point& pt1, const Point& pt2 )
{
	DrawLine(pen, pt1.X, pt1.Y, pt2.X, pt2.Y);
}

void Graphics::DrawLine( Pen& pen, int X1, int Y1, int X2, int Y2 )
{
	DrawLine(pen, static_cast<float>(X1), 
		static_cast<float>(Y1), 
		static_cast<float>(X2), 
		static_cast<float>(Y2));
}

void Graphics::DrawLine( Pen& pen, float X1, float Y1, float X2, float Y2 )
{
	X1 += offset_.X;
	Y1 += offset_.Y;
	X2 += offset_.X;
	Y2 += offset_.Y;
	if (enabled_)
		hge_->Gfx_RenderLine(X1, Y1, X2, Y2, pen.color.get_ARGB());
}

void Graphics::FillRectangle( SolidBrush& brush, const Rectangle& rect )
{
	FillRectangle(brush, rect.Location.X, rect.Location.Y, rect.Size.Width, rect.Size.Height);
}

void Graphics::FillRectangle( SolidBrush& brush, int X, int Y, int Width, int Height )
{
	hgeQuad quad;
	hgeVertex vertex;

	X += offset_.X;
	Y += offset_.Y;

	vertex.col = brush.get_Color().get_ARGB();
	vertex.z = UI_Z;

	vertex.x = X;
	vertex.y = Y;
	quad.v[0] = vertex;

	vertex.x = X + Width;
	vertex.y = Y;
	quad.v[1] = vertex;

	vertex.x = X + Width;
	vertex.y = Y + Height;
	quad.v[2] = vertex;

	vertex.x = X;
	vertex.y = Y + Height;
	quad.v[3] = vertex;

	quad.tex = 0;
	quad.blend = BLEND_DEFAULT;

	if (enabled_)
		hge_->Gfx_RenderQuad(&quad);
}

void Graphics::FillRectangle( Brush& brush, const Rectangle& rect )
{
	switch (brush.get_Type())
	{
	case Brush::Solid:
		FillRectangle(static_cast<SolidBrush&>(brush), rect);
		break;
	}
}

void Graphics::FillRectangle( Brush& brush, int x, int y, int width, int height )
{
	switch (brush.get_Type())
	{
	case Brush::Solid:
		FillRectangle(static_cast<SolidBrush&>(brush), x, y, width, height);
		break;
	}
}

void Graphics::SetClip( const Rectangle& rect )
{
	SetClip(rect.Location.X, rect.Location.Y, rect.Size.Width, rect.Size.Height);
}

void Graphics::SetClip( int X, int Y, int Width, int Height )
{
	int sw = hge_->System_GetState(HGE_SCREENWIDTH);
	int sh = hge_->System_GetState(HGE_SCREENHEIGHT);

	if (X == 0 && Y == 0 && Width == 0 && Height == 0)
	{
		enabled_ = false;
		return;
	}

	X += offset_.X;
	Y += offset_.Y;

	if (Width < 0)
	{
		X += Width; Width = -Width;
	}
	if (Height < 0)
	{
		Y += Height; Height = -Height;
	}

	if (X < 0 && Width < 0 ||
		Y < 0 && Height < 0 ||
		X > sw || 
		Y > sh)
	{
		enabled_ = false;
	}
	else
	{
		enabled_ = true;
		if (X < 0)
		{
			Width += X; X = 0; 
		}
		if (Y < 0)
		{
			Height += Y; Y = 0;
		}
		if (Width < 0 || Height < 0)
			enabled_ = false;
		else
			hge_->Gfx_SetClipping(X, Y, Width, Height);
	}
}

void Graphics::DrawRectangle( Pen& pen, const Rectangle& rect )
{
	DrawRectangle(pen, rect.Location.X, rect.Location.Y, rect.Size.Width, rect.Size.Height);
}

void Graphics::DrawRectangle( Pen& pen, int X, int Y, int Width, int Height )
{
	DrawLine(pen, X, Y, X, Y + Height);
	DrawLine(pen, X, Y + Height, X + Width, Y + Height);
	DrawLine(pen, X + Width, Y, X + Width, Y + Height);
	DrawLine(pen, X, Y, X + Width, Y);
}

void Graphics::DrawImage( const Drawing::Image& image, Point pt )
{
	DrawImage(image, Drawing::Rectangle(pt, image.Size()));
}

void Graphics::DrawImage( const Drawing::Image& image, const Rectangle& rect )
{
	DrawImage(image, rect.Location.X, rect.Location.Y, rect.Size.Width, rect.Size.Height);
}

void Graphics::DrawImage( const Image& image, int X, int Y, int Width, int Height )
{
	X += offset_.X;
	Y += offset_.Y;
	Size size = image.Size();
	if (size.Width == 0 || size.Height == 0)
		return;

	hgeSprite sprite(reinterpret_cast<HTEXTURE>(image.GetHowFromImage()), 0, 0,
		size.Width, size.Height);

	float hscale = static_cast<float>(Width) / size.Width;
	float vscale = static_cast<float>(Height) / size.Height;

	if (enabled_)
		sprite.RenderEx(X, Y, 0, hscale, vscale);
}

void Graphics::DrawString( const String& s, const Font& font, SolidBrush& brush, const PointF& pt )
{
	PointF pos(pt);
	pos.X += offset_.X;
	pos.Y += offset_.Y;

	PHGE hge;
	FontImpl& fi = *reinterpret_cast<FontImpl*>(font.ToHfont());
	pos.Y += fi.get_Height();

	utf32_t prev_code = 0;
	for (String::const_iterator iter = s.begin();
		iter != s.end(); ++iter)
	{
		Glyph* glyph = fi.get_Glyph(*iter);
		if (glyph != NULL && glyph->get_Texture().IsValid())
		{
			Texture& texture = glyph->get_Texture();
			texture.Render(hge, pos.X + glyph->get_X(), 
				pos.Y + glyph->get_Y(), brush.get_Color());

			pos.X += glyph->get_AdvanceX() + fi.get_Kerning(prev_code, *iter).X;
		}
		else
		{
			pos.X += fi.get_Size();
		}
	}
}

void Graphics::DrawString( const String& s, const Font& font, Brush& brush, const PointF& pt )
{
	switch (brush.get_Type())
	{
	case Brush::Solid:
		DrawString(s, font, static_cast<SolidBrush&>(brush), pt);
		break;
	}
}

SizeF Graphics::MeasureString( const String& text, const Font& font )
{
	float height = 0.f;
	float width	= 0.f;
	FontImpl& fi = *reinterpret_cast<FontImpl*>(font.ToHfont());
	for (String::const_iterator iter = text.begin();
		iter != text.end(); ++iter)
	{
		Glyph* glyph = fi.get_Glyph(*iter);
		if (glyph != NULL)
		{
			height = max(height, glyph->get_Height());
			width += glyph->get_Width();
			// TODO: add kerning here.
		}
	}
	return SizeF(width, height);
}

}}}}
