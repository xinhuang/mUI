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

#ifndef __MOUSEBUTTONS_H__
#define __MOUSEBUTTONS_H__

#include <System/System.h>
#include "Export.h"

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY MouseButtons
{
public:
	enum Tag
	{
		None,
		Left,
		Right,
		Middle,
		XButton1,
		XButton2
	};

	MouseButtons() : tag_(None) {}
	MouseButtons(Tag t) : tag_(t) {}

	operator Tag() const { return tag_; }

	bool operator==(Tag t) const { return tag_ == t; }
	bool operator!=(Tag t) const { return !(tag_ == t); }
	
private:
	Tag tag_;
};

}}}

#endif // __MOUSEBUTTONS_H__
