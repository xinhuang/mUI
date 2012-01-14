#include "TextBox.h"

#include <System.Drawing/Drawing.h>
using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

struct TextBox::Data
{
	FormBorderStyle::Enum borderStyle;
	Size textBounds;
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
	DrawBorder(e->Graphics, e->ClipRectangle);

	if (get_Focused())
	{
	}
}

void TextBox::AdjustSize()
{
	Graphics* g = CreateGraphics();
	_d->textBounds = g->MeasureString(get_Text(), *get_Font()).ToSize();

	if (!get_AutoSize() 
		|| (get_Anchor() & AnchorStyles::LeftRight) == AnchorStyles::LeftRight
		|| (get_Anchor() & AnchorStyles::TopBottom) == AnchorStyles::TopBottom)
		return;

	set_Size(_d->textBounds);
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

void TextBox::set_BorderStyle( FormBorderStyle::Enum borderStyle )
{
	_d->borderStyle = borderStyle;
	Update();
}

void TextBox::DrawBorder( Graphics& g, Rectangle& clipRectangle )
{
	if (get_BorderStyle() == FormBorderStyle::None)
		return;

	g.DrawRectangle(Pen(Color::Black), Rectangle(0, 0, get_Width(), get_Height()));
}

FormBorderStyle::Enum TextBox::get_BorderStyle() const
{
	return _d->borderStyle;
}

void TextBox::OnTextChanged( EventArgs* e )
{
	base::OnTextChanged(e);
	AdjustSize();
	Update();
}

}}}
