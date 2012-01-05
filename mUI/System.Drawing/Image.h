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

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <System/System.h>
#include "Size.h"

namespace mUI{ namespace System{ 
	class String;
}}

namespace mUI{ namespace System{  namespace Drawing{

class DRAWING_ENTRY Image
{
public:
	static Image* FromFile(const String& filename);

	virtual ~Image() {}

	virtual Drawing::Size get_Size() const = 0;
	virtual IntPtr GetHowFromImage() const = 0;

	int get_Width() const { return get_Size().Width; }
	int get_Height() const { return get_Size().Height; }

protected:
	Image() {}
	Image(const Image& image) {}
	void operator=(const Image& image) {}
};

}}}

#endif 
