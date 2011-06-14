﻿/*
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

#ifndef __FORMBOARDERSTYLE_H__
#define __FORMBOARDERSTYLE_H__
//
////warning C4482: nonstandard extension used: enum 'mUI::System::Forms::FormBorderStyle' used in qualified name
//#pragma warning(disable:4482)

namespace mUI{ namespace System{  namespace Forms{

class MUI_ENTRY FormBorderStyle
{
public:
	enum FBS {
		None,
		FixedSingle,
		Fixed3D,			// Not supported yet
		FixedDialog,		// Not supported yet
		Sizable,			// Not supported yet
		FixedToolWindow,	// Not supported yet
		SizableToolWindow,	// Not supported yet
	};

	FormBorderStyle() : fbs_(None)
	{}
	FormBorderStyle(FBS fbs) : fbs_(fbs)
	{}

	operator FBS() const { return fbs_; }

private:
	FBS fbs_;
};

}}}

#endif 
