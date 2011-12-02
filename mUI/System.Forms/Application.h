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

#include <Windows.h>

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
	static bool DoEvents();

	static void set_HgeContext(const HgeContext& context);

protected:

	// HGE functions
	static bool InitFunc();
	static bool FrameFunc();
	static bool RenderFunc();

	// Clean Up
	void Dispose();
	void OnFormClose( void* sender, EventArgs* e );

private:
	Application();
	~Application();

	static LRESULT CALLBACK Application::ProcEvents( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

	bool IsDisposing() const;
private:
	HWND			_hwnd;
	Frame*			_frame;
	WNDPROC			_prevWndProc;
	bool			_initializing;
	bool			_disposing;

	static Application _application;
};

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

}}}

#endif // __APPLICATION_H__
