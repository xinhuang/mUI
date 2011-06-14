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

#include "../mUIBase.h"

namespace mUI{ namespace System{  namespace Forms{

class MUI_ENTRY CaptionButton
{
public:
	enum CB{
		Close,
		Help,
		Maximize,
		Minimize,
		Restore,
	};

	CaptionButton(CB cb) : cb_(cb) {}
	CaptionButton& operator=(const CaptionButton& cb) { cb_ = cb.cb_; return *this; }
	bool operator==(const CaptionButton& cb) { return cb_ == cb.cb_; }
	bool operator!=(const CaptionButton& cb) { return cb_ != cb.cb_; }

private:
	CB cb_;
};

}}}
