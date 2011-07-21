#include "InfoForm.h"

#include "PHGE.h"

InfoForm::InfoForm(void) : form_number_(0)
{
	InitializeComponent();
}

InfoForm::~InfoForm(void)
{
}

void InfoForm::InitializeComponent()
{
	Paint += PaintEventHandler(this, &InfoForm::InfoForm_OnPaint);

	set_Size(Size(200, 36));
	set_BackColor(0x80333399);
	set_TopMost(true);
}

void InfoForm::InfoForm_OnPaint( void* sender, PaintEventArgs* e )
{
	PHGE hge;
	wchar_t buffer[128];
	_snwprintf_s(buffer, sizeof(buffer) / 2 - 1, sizeof(buffer) - 1, L"FPS: %3d", hge->Timer_GetFPS());

	SolidBrush brush(Color::Red);
	e->Graphics.DrawString(buffer, *SystemFonts::DefaultFont, brush, PointF(0.f, 0.f));

	_snwprintf_s(buffer, sizeof(buffer) / 2 - 1, sizeof(buffer) - 1, L"Number of Forms: %4d", form_number_);
	e->Graphics.DrawString(buffer, *SystemFonts::DefaultFont, brush, PointF(0.f, 18.f));
}

void InfoForm::set_FormNumber( size_t n )
{
	form_number_ = n;
}
