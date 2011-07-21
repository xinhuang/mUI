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

#ifndef __MUI_GLYPH_H__
#define __MUI_GLYPH_H__

#include "../../System.h"

#include "../HGEDrawing/hgeTexture.h"

namespace mUI{ namespace System { namespace Drawing{

using HGEDrawing::Texture;

class Glyph
{
public:
	Glyph(utf32_t code, const argb_t* buffer, 
		size_t width, size_t height,
		int x, int y, 
		int adv_x, int adv_y);
	Glyph(utf32_t code, const int8_t* grey_buffer, 
		size_t width, size_t height,
		int x, int y, 
		int adv_x, int adv_y);
	~Glyph();

	utf32_t		get_Code()		const;
	Texture&	get_Texture();
	const Texture&	get_Texture()	const;
	size_t		get_Width()		const;
	size_t		get_Height()	const;
	size_t		get_HorizonOffset() const;
	int			get_X() const;
	int			get_Y() const;
	int			get_AdvanceX()	const;
	int			get_AdvanceY()	const;

private:
	utf32_t code_;
	size_t width_;
	size_t height_;
	int x_;
	int y_;
	int adv_x_;
	int adv_y_;
	Texture tex_;
};

}}}

#endif // __MUI_GLYPH_H__
