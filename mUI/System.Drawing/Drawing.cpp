#include "Drawing.h"

#include "Internals/hgeGraphics.h"

namespace mUI{ namespace System{  namespace Drawing{

// -------------------------------------------------------------------- //

void CreateSystemFonts()
{
	SystemFonts::DefaultFont = new Font(L"res/arial.ttf", 10);
	assert(SystemFonts::DefaultFont != NULL);
}

void FreeSystemFonts()
{
	delete SystemFonts::DefaultFont;
	SystemFonts::DefaultFont = NULL;
}

bool InitializeFont()
{
	bool r;
	r = Font::Initialize();
	assert(r && "InitializeFont() failed!");
	CreateSystemFonts();
	return r;
}

bool DisposeFont()
{
	FreeSystemFonts();
	return Font::Dispose();
}

 // -------------------------------------------------------------------- //

Graphics* CreateGraphics( const Rectangle& clip_rect )
{
	return new HGEDrawing::Graphics(clip_rect);
}

bool Initialize()
{
	bool ret;
	ret = InitializeFont();
	assert(ret);
	return true;
}

void Dispose()
{
	bool ret;
	ret = DisposeFont();
	assert(ret);
}

}}}
