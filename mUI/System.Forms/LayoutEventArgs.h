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

#ifndef __LAYOUTEVENTARGS_H__
#define __LAYOUTEVENTARGS_H__

#include <System/System.h>

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY LayoutEventArgs : public EventArgs
{
public:
	LayoutEventArgs(Control* affected_control, const String& affected_property) :
		AffectedControl(affected_control), AffectedProperty(affected_property)
	{}

	//Component* AffectedComponent;
	Control* AffectedControl;
	String AffectedProperty;
};

typedef EventHandler<LayoutEventArgs*> LayoutEventHandler;

}}}

#endif
