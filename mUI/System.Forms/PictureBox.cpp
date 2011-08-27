#include "PictureBox.h"

#include <System.Drawing/Drawing.h>
using mUI::System::Drawing::Pen;

#include "Application.h"

namespace mUI{ namespace System{  namespace Forms{

PictureBox::PictureBox() : image_(NULL)
{

}

PictureBox::~PictureBox()
{
	delete image_;
	image_ = NULL;
	image_location_.clear();
}

void PictureBox::OnPaint( PaintEventArgs* e )
{
	Control::OnPaint(e);

	Graphics& g = e->Graphics;

	if (get_Image() != NULL)
	{
		switch (get_BackgroundImageLayout())
		{
		case ImageLayout::None:
			g.DrawImage(*get_Image(), Point::Empty);
			break;

		case ImageLayout::Stretch:
			g.DrawImage(*get_Image(), e->ClipRectangle);
			break;
		}
	}

	Pen pen(Color::Black);
	g.DrawRectangle(pen, 1, 1, get_ClientSize().Width - 1, get_ClientSize().Height - 1);
}

void PictureBox::Load( String ImageLocation )
{
	image_location_ = ImageLocation;
	set_Image(*Drawing::Image::FromFile(ImageLocation));
}

void PictureBox::set_Image( Drawing::Image& image )
{
	if (image_ != &image)
	{
		delete image_;
		image_ = &image;
		image_location_.clear();
	}
}

void PictureBox::set_ImageLocation( const String& image_location )
{
	Load(image_location);
}

}}}
