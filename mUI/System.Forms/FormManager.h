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
#ifndef __FORMMANAGER_H__
#define __FORMMANAGER_H__

#include <System/System.h>
#include "Export.h"

#include <deque>
#include <map>
using namespace std;

namespace mUI{ namespace System{  namespace Drawing{
	class Point;
}}}
using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

class Form;
class Control;

class FORMS_ENTRY FormManager
{
public:
	static bool Initialize();
	static void Dispose();
	static FormManager& get_Instance();

	void set_RootForm(Form& form);
    Form* get_RootForm();

	void Render();
	void DoEvents();

	void RegisterForm(Form& form);
	void UnregisterForm(Form& form);
	void BringToFront(Form& form);

	IntPtr RegisterControl(Control& ctrl);
	void UnregisterControl(Control& ctrl);
	Control* FromHandle(const IntPtr& h);

	Form* get_ActiveForm() const;

	Form* FormAt(const Point& location);
	Control* ControlAt(const Point& pt);

	Point MapWindowPoint(IntPtr from, IntPtr to, Point pt);

	static Point DeleteMe_GetControlFrameCoord(const Control& control);

	void RaiseMouseEvent(unsigned int message, IntPtr wParam, IntPtr lParam);
	void RaiseKeyboardEvent(unsigned int message, IntPtr wParam, IntPtr lParam);

	void OnFrameActivated();
	void OnFrameDeactivated();

private:
	FormManager();
	~FormManager();
	Form* get_Form(IntPtr handle);
	const Form* get_Form(IntPtr handle) const;

private:
	struct Data;
	Data* _d;
};

}}}

#endif
