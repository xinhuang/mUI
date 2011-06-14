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

#ifndef __TITLEBAR_H__
#define __TITLEBAR_H__

#include "Control.h"
#include "Button.h"
#include "Form.h"

namespace mUI{ namespace System{  namespace Forms{

/*
 * This class is intended for internal use only.
*/

class Form::TitleBar : public Control
{
public:
	TitleBar(Form& form);
	virtual ~TitleBar();

protected:
	void InitializeComponent();

private:
	void TitleBar_OnCloseClick	( void* sender, EventArgs e );
	void TitleBar_OnPaint		( void* sender, PaintEventArgs e );
	void TitleBar_OnMouseDown	( void* sender, MouseEventArgs e );
	void TitleBar_OnMouseUp		( void* sender, MouseEventArgs e );
	void TitleBar_OnMouseMove	( void* sender, MouseEventArgs e );

	void Form_OnDeactivate		( void* sender, EventArgs e );
	void Form_OnSizeChanged		( void* sender, EventArgs e );

	void StartMoving(const Point& pt);
	void Moving(const Point& pt);
	void StopMoving();

private:
	bool moving_;
	Point prev_pt_;

	Button close_;

private:
	static const int TITLE_BAR_HEIGHT = 24;
	static const int BUTTON_WIDTH = 20;
	static const int BUTTON_HEIGHT = 20;
};

}}}

#endif

