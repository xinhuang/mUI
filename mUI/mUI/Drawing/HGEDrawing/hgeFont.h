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

#ifndef __HGE_FONT_H__
#define __HGE_FONT_H__

#include "../IFont.h"
#include <HGE.h>
#include <hgesprite.h>
#include "../../String.h"

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

class Font : public Drawing::IFont
{
public:
	Font(const String& family_name, float size);
	virtual ~Font();

	virtual int get_Size() const;
	virtual const String& get_FontFamily() const;

	// Interfaces for HGEDrawing
	hgeSprite get_Sprite(wchar_t c);

protected:
	void _Load();

private:
	HTEXTURE texture_;
	const String family_name_;
	float size_;
};

}}}}

#endif 
