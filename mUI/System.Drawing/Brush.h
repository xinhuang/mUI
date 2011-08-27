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

#ifndef __BRUSH_H__
#define __BRUSH_H__

#include "Export.h"

namespace mUI{ namespace System{  namespace Drawing{

class DRAWING_ENTRY Brush
{
public:
	virtual ~Brush() {}

	enum Type
	{
		Solid,
		Texture,
	};
	Type get_Type() const { return type_; }

protected:
	Brush(Type type) : type_(type)
	{
	}


private:
	const Type type_;
};

}}}

#endif // __BRUSH_H__
