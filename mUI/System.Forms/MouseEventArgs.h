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

#ifndef __MOUSEEVENTARGS_H__
#define __MOUSEEVENTARGS_H__

#include "MouseButtons.h"
#include "Export.h"

#include <System/System.h>
#include <System.Drawing/Drawing.h>

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY MouseEventArgs : public EventArgs
{
public:
    MouseEventArgs() {}
    MouseEventArgs(MouseButtons button, int clicks, int delta, const Drawing::Point& location)
        : Button(button)
        , Clicks(clicks)
        , Delta(delta)
        , Location(Location)
    {}

	MouseButtons Button;
	int Clicks;
	int Delta;
	Drawing::Point Location;
};

typedef EventHandler<MouseEventArgs*> MouseEventHandler;

}}}

#endif // __MOUSEEVENTARGS_H__
