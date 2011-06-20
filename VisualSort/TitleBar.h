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

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;

class TitleBar :
	public Control
{
public:
	TitleBar();
	virtual ~TitleBar();

private:
	void InitializeComponent();
	void TitleBar_OnMouseDown	( void* sender, MouseEventArgs* e );
	void TitleBar_OnMouseMove	( void* sender, MouseEventArgs* e );
	void TitleBar_OnMouseUp		( void* sender, MouseEventArgs* e );
	void TitleBar_OnLeave		( void* sender, EventArgs* e );
	void TitleBar_OnPaint		( void* sender, PaintEventArgs* e );

private:
	bool moving_;
	Point down_loc_;
};

#endif
