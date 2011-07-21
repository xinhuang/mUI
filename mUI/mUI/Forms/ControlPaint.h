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

#include "../System.h"
#include "ButtonState.h"

namespace mUI{ namespace System{ namespace Drawing{
	class Graphics;
	class Rectangle;
}}}

namespace mUI{ namespace System{  namespace Forms{

class CaptionButton;
class ButtonState;

class MUI_ENTRY ControlPaint
{
public:
	static void DrawCaptionButton(Drawing::Graphics& g, const Drawing::Rectangle& rect,
		const CaptionButton& button, const ButtonState& button_state);
};

}}}
