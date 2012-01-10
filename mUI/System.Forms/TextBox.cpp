#include "TextBox.h"

#include <System.Drawing/Drawing.h>
using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

struct TextBox::Data
{
	FormBorderStyle borderStyle;
};

TextBox::TextBox() : _d(new Data())
{
}

TextBox::~TextBox()
{
	delete _d;
}

void TextBox::OnPaint( PaintEventArgs* e )
{
	base::OnPaint(e);
	e->Graphics.DrawString(get_Text(), *get_Font(), SolidBrush(get_ForeColor()), PointF::Empty);
}

void TextBox::set_Text( const String& text )
{
	base::set_Text(text);
	AdjustSize();
	Update();
}

void TextBox::AdjustSize()
{
	if (!get_AutoSize() 
		|| (get_AnchorStyles() & AnchorStyles::LeftRight) == AnchorStyles::LeftRight
		|| (get_AnchorStyles() & AnchorStyles::TopBottom) == AnchorStyles::TopBottom)
		return;

	Graphics* g = CreateGraphics();
	Size textSize = g->MeasureString(get_Text(), *get_Font()).ToSize();
	set_Size(textSize);
}

void TextBox::set_AutoSize( bool value )
{
	base::set_AutoSize(value);
	AdjustSize();
}

void TextBox::OnKeyPress( KeyPressEventArgs* e )
{
	set_Text(get_Text() + e->KeyChar);
}

void TextBox::set_BorderStyle( FormBorderStyle borderStyle )
{
	_d->borderStyle = borderStyle;
	Update();
}

}}}
