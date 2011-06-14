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

#ifndef __FONT_H__
#define __FONT_H__

#include "../mUIBase.h"

namespace mUI{ namespace System{
	class String;
}}

namespace mUI{ namespace System{ namespace Drawing{

class IFont;

class MUI_ENTRY Font
{
public:
	Font(const String& family_name, float size);
	virtual ~Font();

	int get_Size() const;
	const String& get_FontFamily() const;

	IntPtr ToHfont() const;
	
private:
	IFont* impl_;
};

}}}

#endif
