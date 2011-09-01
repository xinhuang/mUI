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

#ifndef __IFONT_H__
#define __IFONT_H__

#ifdef CreateFont
#	undef CreateFont
#endif

#include <System/System.h>
#include "../Point.h"

namespace mUI{ namespace System{ namespace Drawing{

class Glyph;

class FontImpl
{
public:
	static bool Initialize();
	static bool Dispose();
	static FontImpl* CreateFont(const String& family_name, float size);

	virtual ~FontImpl() {}

	// Basic properties.
	virtual bool	get_Bold()				const = 0;
	virtual bool	get_Italic()			const = 0;
	virtual bool	get_Strikeout()			const = 0;
	virtual bool	get_Underline()			const = 0;

	virtual size_t	get_Height()			const = 0;
	virtual float	get_Size()				const = 0;
	virtual float	get_SizeInPoints()		const = 0;

	virtual const String get_Name()		const = 0;

	// virtual const FontStyle& get_FontStyle() const  = 0;
	// virtual GraphicsUnit get_Unit() = 0;

	// Operations
	virtual Glyph* get_Glyph(utf32_t code)	const = 0;
	virtual Point get_Kerning(utf32_t left, utf32_t right) const = 0;
};

}}}

#endif
