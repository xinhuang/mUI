#include "Image.h"

#include "Internals/hgeImage.h"

namespace mUI{ namespace System{  namespace Drawing{

Image* Image::FromFile( const String& filename )
{
	return HGEDrawing::Image::FromFile(filename);
}

}}}
