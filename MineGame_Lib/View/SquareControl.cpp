#include "SquareControl.h"

#include "MGameForm.h"

SquareControl::SquareControl(int x, int y)
    : _imageIndex(SquareViewState::Covered)
	, _coordinates(x, y)
{
    const static wchar_t* imageResources[SquareViewState::Max] = 
	{
		L"res/coverred.png",
		L"res/flat.png",
        L"res/flag_1.png",
        L"res/flag_2.png",
        L"res/flag_3.png",
        L"res/flag_4.png",
        L"res/flag_5.png",
        L"res/flag_6.png",
        L"res/flag_7.png",
        L"res/flag_8.png",
		L"res/mine.png",
		L"res/boom.png",
		L"res/flag.png",
        L"res/question.png",
        L"res/wrong.png",
    };

    for (int i = 0; i < sizeof(imageResources) / sizeof(imageResources[0]); ++i)
    {
        _imageList.push_back(Image::FromFile(imageResources[i]));
    }

    set_Size(get_ImageSize());
}

SquareControl::~SquareControl()
{
    for (size_t i = 0; i < _imageList.size(); ++i)
    {
        delete _imageList[i];
    }
}

void SquareControl::OnPaint( PaintEventArgs* e )
{
    Graphics& g = e->Graphics;

    g.DrawImage(*_imageList.at(_imageIndex), Point::Empty);
}

const Size& SquareControl::get_ImageSize()
{
	static Size size(16, 16); return size;
}

void SquareControl::OnMouseClick( MouseEventArgs* e )
{
	MGameForm* form = static_cast<MGameForm*>(get_Parent());
	switch (e->Button)
	{
	case MouseButtons::Left:
		form->Uncover(this);
		break;

	case MouseButtons::Right:
		form->ToggleFlag(this);
		break;
	}
}

void SquareControl::set_State( SquareViewState::Enum state )
{
	_imageIndex = state;
}

void SquareControl::set_Coordinates( int x, int y )
{
	_coordinates.X = x;
	_coordinates.Y = y;
}
