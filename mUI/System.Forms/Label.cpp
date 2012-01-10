#include "Label.h"

#include <System.Drawing/Drawing.h>
using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

void Label::OnPaint( PaintEventArgs* e )
{
	base::OnPaint(e);
	e->Graphics.DrawString(get_Text(), *get_Font(), SolidBrush(get_ForeColor()), PointF::Empty);
}

void Label::set_Text( const String& text )
{
	base::set_Text(text);
	AdjustSize();
	Update();
}

void Label::AdjustSize()
{
	if (!get_AutoSize() 
		|| (get_Anchor() & AnchorStyles::LeftRight) == AnchorStyles::LeftRight
		|| (get_Anchor() & AnchorStyles::TopBottom) == AnchorStyles::TopBottom)
		return;

	Graphics* g = CreateGraphics();
	Size textSize = g->MeasureString(get_Text(), *get_Font()).ToSize();
	set_Size(textSize);
}

void Label::set_AutoSize( bool value )
{
	base::set_AutoSize(value);
	AdjustSize();
}

}}}
