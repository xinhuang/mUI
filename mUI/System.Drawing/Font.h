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

#ifndef __MUI_FONT_H__
#define __MUI_FONT_H__

#include "Export.h"
#include <System/System.h>

namespace mUI{ namespace System{ namespace Drawing{

class FontImpl;

class DRAWING_ENTRY Font
{
public:
	Font(const String& family_name, float size);
	virtual ~Font();

	bool	get_Bold()				const;
	bool	get_Italic()			const;
	bool	get_Strikeout()			const;
	bool	get_Underline()			const;

	size_t	get_Height()			const;
	//float	get_Size()				const;
	float	get_SizeInPoints()		const;

	const String get_Name()		const;

	IntPtr ToHfont() const;

protected:
	friend bool InitializeFont();
	static bool Initialize();
	friend bool DisposeFont();
	static bool Dispose();
	
private:
	FontImpl* impl_;
};

}}}

#endif // __MUI_FONT_H__
