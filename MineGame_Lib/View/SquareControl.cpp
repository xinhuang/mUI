#include "SquareControl.h"

#include "MGameForm.h"

SquareControl::SquareControl(MGameForm* form, int x, int y)
    : _imageIndex(SquareViewState::Covered)
	, _location(x, y)
	, _gameForm(form)
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
	switch (e->Button)
	{
	case MouseButtons::Left:
		_gameForm->Uncover(this);
		break;

	case MouseButtons::Right:
		_gameForm->ToggleFlag(this);
		break;
	}
}

void SquareControl::set_State( SquareViewState::Enum state )
{
	_imageIndex = state;
}
