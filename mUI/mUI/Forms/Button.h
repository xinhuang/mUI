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

#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "ButtonBase.h"

#include "../System.h"

namespace mUI{ namespace System{ namespace Drawing{
	class Image;
}}}

namespace mUI{ namespace System{  namespace Forms{

class MUI_ENTRY Button : public ButtonBase
{
public:
	Button();
	virtual ~Button();

	void set_NormalImage(const String& image);			// Non-WinForm interface!
	void set_HoverImage(const String& image);			// Non-WinForm interface!
	void set_PressedImage(const String& image);			// Non-WinForm interface!

protected:
	virtual void OnPaint			( PaintEventArgs* e );

	virtual void OnMouseEnter		( EventArgs* e );
	virtual void OnMouseHover		( EventArgs* e );
	virtual void OnMouseDown		( MouseEventArgs* e );
	virtual void OnMouseUp			( MouseEventArgs* e );
	virtual void OnMouseMove		( MouseEventArgs* e );
	virtual void OnMouseLeave		( EventArgs* e );

	virtual void OnLeave			( EventArgs* e );

private:
	enum State
	{
		Normal		= 0,
		Hover		= 1,
		Pressed		= 2,
		StateMax	= 3,
		HoverPressed = Hover | Pressed,
	};
	void set_StateImage( State s, const String& image );

private:
	Color normal_color_;
	Color pressed_color_;
	State state_;
	Drawing::Image *state_images_[StateMax];
};

}}}

#endif
