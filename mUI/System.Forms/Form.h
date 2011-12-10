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

#ifndef __FORM_H__
#define __FORM_H__

#include <System/System.h>
#include "Control.h"
#include "FormBoarderStyle.h"
#include "Button.h"

namespace mUI{ namespace System{  namespace Forms{

typedef Delegate<void> MethodInvoker;

class FORMS_ENTRY Form : public Control
{
public:
	EventHandler<> Load;			// TODO: Occurs before a form is displayed for the first time.

	EventHandler<> Closing;
	EventHandler<> Closed;

	EventHandler<> Activated;
	EventHandler<> Deactivate;

	EventHandler<> BorderStyleChanged;

	Form();
	virtual ~Form();

	static Form* get_ActiveForm();

	bool get_TopMost() const { return topmost_; }
	void set_TopMost(bool value);

	virtual void Close();

	virtual Point PointToScreen(Point pt) const;

	const FormBorderStyle& get_FormBorderStyle() const;
	void set_FormBorderStyle(const FormBorderStyle& style);

	Size get_ClientSize() const;

protected:
	friend class Application;
	friend class FormManager;
	void InitializeComponent();

	virtual void OnLoad					( EventArgs* e );
	virtual void OnClosing				( EventArgs* e );
	virtual void OnClosed				( EventArgs* e );
	virtual void OnPaint				( PaintEventArgs* e );
	virtual void OnEnter				( EventArgs* e );
	virtual void OnLeave				( EventArgs* e );
	virtual void OnActivated			( EventArgs* e );
	virtual void OnDeactivate			( EventArgs* e );
	virtual void OnBorderStyleChanged	( EventArgs* e );

private:
	bool			topmost_;
	FormBorderStyle form_boarder_style_;

private:
	static const int default_width = 800;
	static const int default_height = 600;
};

}}}

#endif // __FORM_H__
