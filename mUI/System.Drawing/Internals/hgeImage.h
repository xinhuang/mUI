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

#ifndef __HGE_IMAGE_H__
#define __HGE_IMAGE_H__

#include "../Image.h"
#include "../Size.h"
#include <HGE.h>
#include "hgeTexture.h"

namespace mUI{ namespace System{  namespace Drawing{ namespace HGEDrawing{

class Image : public Drawing::Image
{
public:
	static Drawing::Image* FromFile(const String& filename);

	virtual ~Image();

	Drawing::Size Size() const;
	virtual IntPtr GetHowFromImage() const;

protected:
	Image(const String& filename);

private:
	Texture texture_;
};

}}}}

#endif 
