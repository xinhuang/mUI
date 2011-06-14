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

#ifndef __BUTTONSTATE_H__
#define __BUTTONSTATE_H__

#include "../mUIBase.h"

namespace mUI{ namespace System{  namespace Forms{

class MUI_ENTRY ButtonState
{
public:
	enum BS{
		Checked		= 0x0001,
		Flat		= 0x0002,
		Inactive	= 0x0004,
		Normal		= 0x0008,
		Pushed		= 0x0010,
		All			= 0x001F
	};

	ButtonState() : bs_(Normal) {}
	ButtonState(BS bs) : bs_(bs) {}
	ButtonState& operator=(const ButtonState& bs) { bs_ = bs.bs_; return *this; }
	bool operator==(const ButtonState& bs) { return bs_ == bs.bs_; }
	bool operator!=(const ButtonState& bs) { return bs_ != bs.bs_; }

private:
	BS bs_;
};

}}}

#endif