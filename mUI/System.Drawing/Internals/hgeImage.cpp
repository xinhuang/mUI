#include "hgeImage.h"

#include "PHGE.h"

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

Drawing::Image* Image::FromFile( const String& filename )
{
	Image* image = new Image(filename);
	assert(image != NULL);

	return image;
}

Image::Image( const String& filename ) : texture_(filename)
{

}

Image::~Image()
{
}

Drawing::Size Image::get_Size() const
{
	PHGE hge;
	int width = texture_.get_Width();
	int height = texture_.get_Height();
	return Drawing::Size(width, height);
}

IntPtr Image::GetHowFromImage() const
{
	return reinterpret_cast<IntPtr>(texture_.get_Texture());
}

}}}}
