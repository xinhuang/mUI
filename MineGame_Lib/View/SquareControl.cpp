#include "SquareControl.h"

SquareControl::SquareControl()
    : _imageIndex(ImageIndex::Coverred)
{
    String imageResources[ImageIndex::Max] = 
    {
        L"boom.png",
        L"coverred.png",
        L"flag.png",
        L"flag_1.png",
        L"flag_2.png",
        L"flag_3.png",
        L"flag_4.png",
        L"flag_5.png",
        L"flag_6.png",
        L"flag_7.png",
        L"flag_8.png",
        L"flat.png",
        L"mine.png",
        L"question.png",
        L"wrong.png",
    };

    for (int i = 0; i < sizeof(imageResources) / sizeof(imageResources[0]); ++i)
    {
        _imageList.push_back(Image::FromFile(imageResources[i]));
    }

    set_Size(Size(16, 16));
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

