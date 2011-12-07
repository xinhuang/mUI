#include "Application.h"

#include <cassert>

#include <tchar.h>
#include <ctime>

#include <Windows.h>

#include <System.Threading/Threading.h>

#include <System.Drawing/Drawing.h>
using namespace mUI::System::Drawing;

#include <System.Drawing/Internals/PHGE.h>
using mUI::System::Drawing::HGEDrawing::PHGE;

#include "Frame.h"
#include "Form.h"
#include "FormManager.h"

// -------------------------------------------------------------------- //

namespace mUI{ namespace System{  namespace Forms{

Application Application::_application;

Application::Application() : 
	_initializing(true), _disposing(false)
{
	bool ret = Threading::Init();
	assert(ret);
	ret = FormManager::Initialize();
	assert(ret);
	srand(static_cast<unsigned int>(time(NULL)));
}

//LRESULT CALLBACK Application::ProcEvents( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
IntPtr __stdcall Application::ProcEvents( IntPtr hWnd, unsigned int message, IntPtr wParam, IntPtr lParam )
{
	if (_application.IsDisposing())
		return reinterpret_cast<IntPtr>(CallWindowProc(
			reinterpret_cast<WNDPROC>(_application._prevWndProc), 
			reinterpret_cast<HWND>(hWnd), 
			message, 
			reinterpret_cast<WPARAM>(wParam), 
			reinterpret_cast<WPARAM>(lParam)));

	if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)
		FormManager::get_Instance().RaiseMouseEvent(message, wParam, lParam);
	else if (message >= WM_KEYFIRST && message <= WM_KEYLAST)
		FormManager::get_Instance().RaiseKeyboardEvent(message, wParam, lParam);
	else
	{
		switch (message)
		{
		case WM_CLOSE:
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			_application.Dispose();
			break;

		case WM_ACTIVATE:
			if (wParam == WA_INACTIVE)
				FormManager::get_Instance().OnFrameDeactivated();
			else
				FormManager::get_Instance().OnFrameActivated();
			break;
		}
	}
	return reinterpret_cast<IntPtr>(CallWindowProc(
		reinterpret_cast<WNDPROC>(_application._prevWndProc), 
		reinterpret_cast<HWND>(hWnd), 
		message, 
		reinterpret_cast<WPARAM>(wParam), 
		reinterpret_cast<LPARAM>(lParam)));
}

bool Application::DoEvents()
{
	bool ret = false;
	if (!_application.IsDisposing() && _application._frame != NULL)
	{
		PHGE hge;
		ret = _application._frame->LogicTick(hge->Timer_GetDelta());
	}

	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{
		if (msg.message != WM_QUIT)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			ret = true;
		}
	}

	FormManager::get_Instance().DoEvents();

	if (ret)
		_application.Dispose();

	return ret;
}

void Application::Run( Frame* frame )
{
	assert(frame != NULL);
	FormManager::get_Instance().set_RootForm(*frame);

	_application._frame = frame;
	frame->Closed += EventHandler<>(_application, &Application::OnFormClose);

	const String& title = frame->get_Text();
	const Drawing::Size& size = frame->get_Size();

	PHGE hge;
	hge->System_SetState(HGE_LOGFILE, "mai.log");
	hge->System_SetState(HGE_FRAMEFUNC, InitFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, title.ToANSI().c_str());

	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, size.Width);
	hge->System_SetState(HGE_SCREENHEIGHT, size.Height);
	hge->System_SetState(HGE_SCREENBPP, 32);

	hge->System_SetState(HGE_FPS, frame->get_Fps());
	hge->System_SetState(HGE_DONTSUSPEND, true);
	hge->System_SetState(HGE_HIDEMOUSE, false);
	
	if (hge->System_Initiate())
	{
		hge->System_Start();
	}
	else
	{
		::MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}
}

void Application::OnFormClose( void* sender, EventArgs* e )
{
	PHGE hge;
	PostMessage(hge->System_GetState(HGE_HWND), WM_CLOSE, 0, 0);
}

void Application::Dispose()
{
	if (IsDisposing())
		return;

	_disposing = true;

	_frame = NULL;
	FormManager::get_Instance().Dispose();
	Threading::Dispose();
	Drawing::Dispose();

	PHGE hge;
	hge->System_Shutdown();
}

bool Application::FrameFunc()
{
	return _application.DoEvents();
}

bool Application::RenderFunc()
{
	PHGE hge;
	hge->Gfx_BeginScene();

	FormManager::get_Instance().Render();

	hge->Gfx_EndScene();
	return false;
}

bool Application::InitFunc()
{
	bool ret = Drawing::Initialize();
	assert(ret);

	PHGE hge;

	HWND hwnd = hge->System_GetState(HGE_HWND);
	assert(hwnd && hwnd != INVALID_HANDLE_VALUE);
	_application._prevWndProc = reinterpret_cast<wndproc_t>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)ProcEvents));

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);

	if (_application._frame != NULL)
	{
		_application._frame->Initialize();
		_application._frame->Show();
	}

	return FrameFunc();
}

Application::~Application()
{
}

bool Application::IsDisposing() const
{
	return _disposing;
}

void Application::InitializeWindow()
{
	bool ret = Drawing::Initialize();
	assert(ret);

	PHGE hge;
	HWND hwnd = hge->System_GetState(HGE_HWND);
	assert(hwnd && hwnd != INVALID_HANDLE_VALUE);
	_prevWndProc = reinterpret_cast<wndproc_t>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)ProcEvents));

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
}

bool Application::PrivateInitialize()
{
	_application.InitializeWindow();
	return true;	// Force quite hge loop. Later re-enter via Run(form)
}

void Application::StartHge( const HgeContext &context )
{
	_application._hge = ::hgeCreate(HGE_VERSION);
	PHGE hge;
	hge->System_SetState(HGE_LOGFILE, context.get_LogFile().ToANSI().c_str());
	hge->System_SetState(HGE_FRAMEFUNC, PrivateInitialize);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, context.get_Title().ToANSI().c_str());

	hge->System_SetState(HGE_WINDOWED, context.get_Windowed());
	hge->System_SetState(HGE_SCREENWIDTH, context.get_Size().Width);
	hge->System_SetState(HGE_SCREENHEIGHT, context.get_Size().Height);
	hge->System_SetState(HGE_SCREENBPP, context.get_ScreenBpp());

	hge->System_SetState(HGE_FPS, context.get_Fps());
	hge->System_SetState(HGE_DONTSUSPEND, context.get_DontSuspent());
	hge->System_SetState(HGE_HIDEMOUSE, context.get_HideMouse());

	if (hge->System_Initiate())
	{
		hge->System_Start();
	}
	else
	{
		::MessageBoxA(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
	}
}

void Application::Run( Form* form )
{
	FormManager::get_Instance().set_RootForm(*form);
	form->Show();

	form->Closed += EventHandler<>(_application, &Application::OnFormClose);

	const String& title = form->get_Text();

	PHGE hge;
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_TITLE, title.ToANSI().c_str());

	hge->System_Start();
}

}}}
