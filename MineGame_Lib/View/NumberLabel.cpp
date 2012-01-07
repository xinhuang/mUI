#include "NumberLabel.h"

using namespace mUI::System::Drawing;

struct NumberLabel::Data
{
	~Data()
	{
	}

	Image* image;
	int value;
};

NumberLabel::NumberLabel()
	: _d(new Data())
{
	InitializeComponents();
}

NumberLabel::~NumberLabel()
{
	delete _d;
}

void NumberLabel::InitializeComponents()
{
	set_Value(0);

	set_BackgroundImage(Image::FromFile(L"res/na.png"));
	set_BackgroundImageLayout(ImageLayout::Tile);
}

void NumberLabel::set_Value( int value )
{
	_d->value = value;
	Update();
}


