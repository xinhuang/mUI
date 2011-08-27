/*
	Copyright 2011 hello.patz@gmail.com

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef __HGE_TEXTURE_H__
#define __HGE_TEXTURE_H__

#include <hge.h>
#include <System/System.h>

namespace mUI{ namespace System{  namespace Drawing{
	class Color;
}}}

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

class PHGE;

class Texture
{
public:
	Texture( const String& file );
	Texture( size_t width, size_t height );
	explicit Texture( const argb_t* buffer, size_t width, size_t height );
	explicit Texture( const int8_t* grey_buffer, size_t width, size_t height );

	~Texture();

	HTEXTURE get_Texture() const;
	const String& get_File() const;
	size_t get_Width() const;
	size_t get_Height() const;

	bool IsValid() const;
	argb_t* Lock() const;
	void Unlock() const;

	void Render(PHGE& hge, float x, float y) const;
	void Render(PHGE& hge, float x, float y, const Color& color) const;

protected:
	void Create( size_t width, size_t height );

private:
	Texture(const Texture&) {}

	void Fill( const argb_t* buffer, size_t height, size_t width );
	void Fill( const int8_t* grey_buffer, size_t height, size_t width );
	void operator=(const Texture&) {}

private:
	const String file_;
	mutable HTEXTURE tex_;
};

}}}}

#endif
