#include "hgeTexture.h"

#include "PHGE.h"
#include <hgesprite.h>

#include "../Drawing.h"

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

Texture::Texture( const String& file ) : file_(file), tex_(0)
{
}

Texture::Texture( size_t width, size_t height ) : tex_(0)
{
	Create(width, height);
}

Texture::Texture( const argb_t* buffer, size_t width, size_t height ) : tex_(0)
{
	Create(width, height);
	Fill(buffer, height, width);
}

Texture::Texture( const int8_t* grey_buffer, size_t width, size_t height ) : tex_(0)
{
	Create(width, height);
	Fill(grey_buffer, height, width);
}

Texture::~Texture()
{
	if (tex_ != 0)
	{
		PHGE hge;
		hge->Texture_Free(tex_);
		tex_ = 0;
	}
}

HTEXTURE Texture::get_Texture() const
{
	if (tex_ == 0)
	{
		PHGE hge;
		tex_ = hge->Texture_Load(get_File().ToANSI().c_str());
	}
	return tex_;
}

const String& Texture::get_File() const
{
	return file_;
}

size_t Texture::get_Height() const
{
	HTEXTURE tex = get_Texture();
	if (tex == 0)
	{
		return 0;
	}
	else
	{
		PHGE hge;
		return hge->Texture_GetHeight(tex);
	}
}

size_t Texture::get_Width() const
{
	HTEXTURE tex = get_Texture();
	if (tex == 0)
	{
		return 0;
	}
	else
	{
		PHGE hge;
		return hge->Texture_GetWidth(tex);
	}
}

bool Texture::IsValid() const
{
	return tex_ != 0;
}

argb_t* Texture::Lock() const
{
	PHGE hge;
	return reinterpret_cast<argb_t*>(hge->Texture_Lock(get_Texture(), false));
}

void Texture::Unlock() const
{
	PHGE hge;
	hge->Texture_Unlock(get_Texture());
}

void Texture::Create( size_t width, size_t height )
{
	PHGE hge;
	tex_ = hge->Texture_Create(width, height);
}

void Texture::Fill( const int8_t* grey_buffer, size_t height, size_t width )
{
	if (!IsValid())
		return;
	size_t tw = get_Width();
	argb_t* tbuf = Lock();
	assert(tbuf != 0);
	for (size_t y = 0; y < height; ++y)
	{
		for (size_t x = 0; x < width; ++x)
		{
			tbuf[y * tw + x] = 0xFFFFFF | (grey_buffer[y * width + x] << 24);
		}
	}
}

void Texture::Fill( const argb_t* buffer, size_t height, size_t width )
{
	if (!IsValid())
		return;

	size_t tw = get_Width();
	argb_t* tbuf = Lock();
	assert(tbuf != 0);
	for (size_t y = 0; y < height; ++y)
	{
		memcpy(tbuf + y * tw, buffer + y * width, sizeof(argb_t) * width);
	}
}

void Texture::Render( PHGE& hge, float x, float y ) const
{
	if (IsValid())
	{
		float w = static_cast<float>(get_Width());
		float h = static_cast<float>(get_Height());
		hgeSprite sprite(get_Texture(), 0.f, 0.f, w, h);
		sprite.Render(x, y);
	}
}

void Texture::Render( PHGE& hge, float x, float y, const Color& color ) const
{
	if (IsValid())
	{
		float w = static_cast<float>(get_Width());
		float h = static_cast<float>(get_Height());
		hgeSprite sprite(get_Texture(), 0.f, 0.f, w, h);
		sprite.SetColor(color.get_ARGB());
		sprite.Render(x, y);
	}
}

}}}}