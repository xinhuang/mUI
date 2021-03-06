﻿#include "MainFrame.h"
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	mUI::System::Forms::Application::Run(new MainFrame());

	return ERROR_SUCCESS;
}

