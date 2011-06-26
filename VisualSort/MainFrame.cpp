#include "MainFrame.h"

#include "PHGE.h"
#include "QuickSortForm.h"

#include <algorithm>
using namespace std;

MainFrame::MainFrame()
{
	set_Text("mUI Example - Visual Sort");
}

int MainFrame::get_Fps() const
{
	return 50;
}

void MainFrame::ShowQuickSortForm( void* sender, EventArgs* e )
{
	QuickSortForm* qsform = new QuickSortForm();
	qsform->Show();

	Random r;
	vector<int> array;
	for (size_t i = 0; i < 10; ++i)
	{
		array.push_back(i + 1);
	}
	for (size_t i = 0; i < array.size(); ++i)
	{
		swap(array[i], array[r.Next(10)]);
	}
	qsform->BeginSort(array);
}

bool MainFrame::Initialize()
{
	Paint += PaintEventHandler(this, &MainFrame::MainFrame_OnPaint);

	show_qsort_.set_Text("Quick Sort");
	show_qsort_.set_Size(Drawing::Size(100, 20));
	show_qsort_.set_Location(Drawing::Point(20, 15));
	show_qsort_.Click += EventHandler<>(this, &MainFrame::ShowQuickSortForm);
	Controls.Add(show_qsort_);

	return true;
}

void MainFrame::MainFrame_OnPaint( void* sender, PaintEventArgs* e )
{
	PHGE hge;
	wchar_t buffer[128];
	_snwprintf_s(buffer, sizeof(buffer) / 2 - 1, sizeof(buffer) - 1, L"FPS: %3d", hge->Timer_GetFPS());

	Brush brush(Color::Red);
	e->Graphics.DrawString(buffer, *SystemFonts::DefaultFont, brush, PointF(0.f, 0.f));
}
