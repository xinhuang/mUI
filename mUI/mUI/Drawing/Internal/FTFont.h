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

#ifndef __MUI_FTFONT_H__
#define __MUI_FTFONT_H__

#include <System/System.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FontImpl.h"

#include <map>
using std::map;

namespace mUI{ namespace System { namespace Drawing{

class Glyph;

class FTFont : public FontImpl
{
public:
	static bool Initialize();
	static bool Dispose();

	FTFont( const String& filename, float font_size );
	FTFont( const void* buffer, size_t cb_buf, float font_size );
	virtual ~FTFont();

	// Freetype2 interfaces
	size_t	get_NumberOfGlyph() const;
	bool	get_Scalable() const;

	// Basic properties.
	virtual bool	get_Bold()				const;
	virtual bool	get_Italic()			const;
	virtual bool	get_Strikeout()			const;
	virtual bool	get_Underline()			const;

	virtual size_t	get_Height()			const;
	virtual float	get_Size()				const;
	virtual float	get_SizeInPoints()		const;

	virtual const String get_Name()		const;

	// Operations
	virtual Glyph* get_Glyph(utf32_t code) const;
	virtual Point get_Kerning(utf32_t left, utf32_t right) const;

protected:
	void set_Size( float font_size );

	void Cache( Glyph* glyph ) const;
	void Decache( utf32_t code ) const;
	bool IsCached( utf32_t code ) const;
	Glyph* FTFont::get_Cache( utf32_t code ) const;

private:
	void Load( const String &filename, size_t index );
	void Load( const void* buffer, size_t cb_buf, size_t index );

private:
	FT_Face face_;
	mutable map<utf32_t, Glyph*> glyph_cache_;

	float ptsize_;

	static FT_Library library_;
	static const int DPI = 96;
};

}}}

#endif
