#include "hgeImage.h"

#include "PHGE.h"

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

Drawing::Image* Image::FromFile( const String& filename )
{
	Image* image = new Image();
	assert(image != NULL);

	PHGE hge;
	image->texture_ = hge->Texture_Load(filename.ToANSI().c_str());
	if (image->texture_ == 0)
	{
		String errmsg = hge->System_GetErrorMessage();
		hge->System_Log("%s", errmsg.ToANSI().c_str());
	}

	return image;
}

Image::~Image()
{
	PHGE hge;
	if (texture_ != 0)
	{
		hge->Texture_Free(texture_);
		texture_ = 0;
	}
}

Drawing::Size Image::Size() const
{
	PHGE hge;
	int width = hge->Texture_GetWidth(texture_, true);
	int height = hge->Texture_GetHeight(texture_, true);
	return Drawing::Size(width, height);
}

IntPtr Image::GetHowFromImage() const
{
	return reinterpret_cast<IntPtr>(texture_);
}

}}}}
