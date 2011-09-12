#include "Application.h"

#include <cassert>

#include <tchar.h>
#include <ctime>

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

Application Application::application_;

Application::Application() : 
	initializing_(true), disposing_(false)
{
	bool ret = Threading::Init();
	assert(ret);
	ret = FormManager::Initialize();
	assert(ret);
	srand(static_cast<unsigned int>(time(NULL)));
}

LRESULT CALLBACK Application::ProcEvents( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (application_.IsDisposing())
		return CallWindowProc(application_.prev_wnd_proc_, hWnd, message, wParam, lParam);

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
			application_.Dispose();
			break;

		case WM_ACTIVATE:
			if (wParam == WA_INACTIVE)
				FormManager::get_Instance().OnFrameDeactivated();
			else
				FormManager::get_Instance().OnFrameActivated();
			break;
		}
	}
	return CallWindowProc(application_.prev_wnd_proc_, hWnd, message, wParam, lParam);
}

bool Application::DoEvents()
{
	bool ret = true;
	if (!application_.IsDisposing())
	{
		PHGE hge;
		ret = application_.frame_->LogicTick(hge->Timer_GetDelta());
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
		application_.Dispose();

	return ret;
}

void Application::Run( Frame* frame )
{
	assert(frame != NULL);
	FormManager::get_Instance().set_MainFrame(*frame);

	application_.frame_ = frame;
	frame->Closed += EventHandler<>(application_, &Application::OnFormClose);

	const String& title = frame->get_Text();
	const Drawing::Size& size = frame->get_Size();

	PHGE hge;
	hge->System_SetState(HGE_LOGFILE, "mai.log");
	hge->System_SetState(HGE_FRAMEFUNC, InitFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, frame->get_Text().ToANSI().c_str());

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

	disposing_ = true;

	frame_ = NULL;
	FormManager::get_Instance().Dispose();
	Threading::Dispose();
	Drawing::Dispose();

	PHGE hge;
	hge->System_Shutdown();
}

bool Application::FrameFunc()
{
	return application_.DoEvents();
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
	application_.prev_wnd_proc_ = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)ProcEvents));

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);

	application_.frame_->Initialize();
	application_.frame_->Show();

	return FrameFunc();
}

Application::~Application()
{
}

bool Application::IsDisposing() const
{
	return disposing_;
}

}}}
