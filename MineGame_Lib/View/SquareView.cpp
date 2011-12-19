#include "SquareView.h"

#include "MineFieldView.h"

SquareView::SquareView()
    : _imageIndex(SquareViewState::Covered)
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

SquareView::~SquareView()
{
    for (size_t i = 0; i < _imageList.size(); ++i)
    {
        delete _imageList[i];
    }
}

void SquareView::OnPaint( PaintEventArgs* e )
{
    Graphics& g = e->Graphics;

    g.DrawImage(*_imageList.at(_imageIndex), Point::Empty);
}

const Size& SquareView::get_ImageSize()
{
	static Size size(16, 16); return size;
}

void SquareView::OnMouseClick( MouseEventArgs* e )
{
	MineFieldView* parent = static_cast<MineFieldView*>(get_Parent());
	switch (e->Button)
	{
	case MouseButtons::Left:
		parent->Uncover(this);
		break;

	case MouseButtons::Right:
		parent->ToggleFlag(this);
		break;
	}
}

void SquareView::set_State( SquareViewState::Enum state )
{
	_imageIndex = state;
}

void SquareView::set_Coordinates(const Point& coord)
{
	_coordinates = coord;
	Point location;
	location.X = coord.X * get_ImageSize().Width;
	location.Y = coord.Y * get_ImageSize().Height;
	set_Location(location);
}
