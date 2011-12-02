#include <View/MainForm.h>
#include <mUI.h>
using namespace mUI::System::Forms;

int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	mUI::Extra::HgeContext context;
	Application::StartHge(context);
	Application::Run(new MainForm());

	return EXIT_SUCCESS;
}