#include "NumberLabel.h"

using namespace mUI::System::Drawing;

struct NumberLabel::Data
{
	Image* image;
};

NumberLabel::NumberLabel()
{
	InitializeComponents();
}

void NumberLabel::OnPaint( PaintEventArgs* e )
{
	int width = _d->image->get_Width();
	e->Graphics.DrawImage(*_d->image, Point(0, 0));
	e->Graphics.DrawImage(*_d->image, Point(width, 0));
	e->Graphics.DrawImage(*_d->image, Point(width * 2, 0));
}

void NumberLabel::InitializeComponents()
{
	_d->image = Image::FromFile(L"res/na.png");
}


