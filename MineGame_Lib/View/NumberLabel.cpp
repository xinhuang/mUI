#include "NumberLabel.h"

#include <sstream>
using namespace std;

using namespace mUI::System::Drawing;

struct NumberLabel::Data
{
	~Data()
	{
		while (imageList.size() > 0)
		{
			delete imageList.back();
			imageList.pop_back();
		}
	}

	vector<Image*> imageList;
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

	for (int i = 0; i < 10; ++i)
	{
		wstringstream sstr;
		sstr << "res/" << i << ".png";
		String imageFile = sstr.str();
		_d->imageList.push_back(Image::FromFile(imageFile));
	}
}

void NumberLabel::set_Value( int value )
{
	_d->value = value;
	Update();
}

void NumberLabel::OnPaint( PaintEventArgs* e )
{
	Control::OnPaint(e);
	int digitsTotal = GetDigitsTotal();
	for (int i = 0; i < digitsTotal; ++i)
	{
		int n = GetDigit(i);
		Point pos = GetDigitPos(i);
		e->Graphics.DrawImage(*_d->imageList[n], pos);
	}
}

int NumberLabel::GetDigitsTotal() const
{
	stringstream sstr;
	sstr << _d->value;
	return sstr.str().length();
}

int NumberLabel::GetDigit( int i ) const
{
	stringstream sstr;
	sstr << _d->value;
	return sstr.str().at(sstr.str().length() - i - 1) - '0';
}

Point NumberLabel::GetDigitPos( int i ) const
{
	int imageWidth = _d->imageList[0]->get_Width();
	return Point(3 * imageWidth - (i + 1) * imageWidth, 0);
}


