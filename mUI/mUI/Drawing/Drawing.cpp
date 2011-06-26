#include "Drawing.h"

#include "HGEDrawing/hgeGraphics.h"

namespace mUI{ namespace System{  namespace Drawing{

Graphics* CreateGraphics( const Rectangle& clip_rect )
{
	return new HGEDrawing::Graphics(clip_rect);
}

void CreateSystemFonts()
{
	SystemFonts::DefaultFont = new Font(L"res/default", 18);
	assert(SystemFonts::DefaultFont != NULL);
}
void FreeSystemFonts()
{
	delete SystemFonts::DefaultFont;
	SystemFonts::DefaultFont = NULL;
}

bool Initialize()
{
	CreateSystemFonts();
	return true;
}

void Dispose()
{
	FreeSystemFonts();
}

}}}
