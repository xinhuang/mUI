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

#ifndef __SOLIDBRUSH_H__
#define __SOLIDBRUSH_H__

#include "../Export.h"
#include "Color.h"
#include "Brush.h"

namespace mUI{ namespace System{  namespace Drawing{

class MUI_ENTRY SolidBrush : public Brush
{
public:
	SolidBrush(const Color& color);

	const Color& get_Color() const;
	Color& get_Color();
	void set_Color(const Color& color);

private:
	Color color_;
};

}}}

#endif // __SOLIDBRUSH_H__
