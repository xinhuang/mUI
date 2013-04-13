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

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <System/System.h>
using mUI::System::EventArgs;

#include <Extra/Extra.h>
using mUI::Extra::HgeContext;

#include "Export.h"

#include <deque>
using std::deque;

class HGE;

// ------------------------------------------------------------

namespace mUI{ namespace System{  namespace Drawing{
	class Graphics;
	class Point;
}}}

using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

class Form;
class Control;
class Frame;

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

class FORMS_ENTRY Application
{
public:
	static void Run(Frame* frame);
	static void Run(Form* form);
	static bool DoEvents();

	static void StartHge(const HgeContext& context);

    static const Size& get_Size();

protected:
	// HGE functions
	static bool InitFunc();
	static bool FrameFunc();
	static bool RenderFunc();
	static bool PrivateInitialize();

	// Clean up
	void Dispose();
	void OnFormClose( void* sender, EventArgs* e );

	void InitializeWindow();

private:
	Application();
	~Application();

	static IntPtr __stdcall ProcEvents( IntPtr hWnd, unsigned int message, IntPtr wParam, IntPtr lParam );

    static void ProcessMiscMessages( unsigned int message, IntPtr wParam );

    static void ProcessKeyboardMessages( unsigned int message, IntPtr wParam, IntPtr lParam );

    static void ProcessMouseMessages( unsigned int message, IntPtr wParam, IntPtr lParam );

    static void OnWindowDestruction();

    static void OnWindowActivation( IntPtr wParam );

    static IntPtr CallPreviousWndProc( IntPtr hWnd, unsigned int message, IntPtr wParam, IntPtr lParam );

    static bool IsKeyboardMessage( unsigned int message );

    static bool IsMouseMessage( unsigned int message );

    typedef IntPtr (__stdcall *wndproc_t)(IntPtr hWnd, unsigned int message, IntPtr wParam, IntPtr lParam);

	bool IsDisposing() const;
private:
	IntPtr			_hwnd;
	Frame*			_frame;
	wndproc_t		_prevWndProc;

	bool			_initializing;
	bool			_disposing;
	bool			_disposed;

	HgeContext		_hgeContext;
	HGE* _hge;

    Size            _windowSize;

	static Application _application;
};

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

}}}

#endif // __APPLICATION_H__
