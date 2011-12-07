#include "VisualSortForm.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
using std::swap;

using namespace mUI::System;

#include "TitleBar.h"

VisualSortForm::VisualSortForm(void) : _worker(NULL)
{
	set_Size(Drawing::Size(500, 400));
	set_Location(Point(100, 100));

	_titleBar = new TitleBar();
	_titleBar->set_Size(Size(this->get_Size().Width - 2, 20));
	Controls.Add(*_titleBar);

	Paint += PaintEventHandler(this, &VisualSortForm::OnPaint);
}

VisualSortForm::~VisualSortForm(void)
{
	Dispose();
}

void VisualSortForm::OnPaint( void* sender, PaintEventArgs* e )
{
	if (_array.size() == 0)
		return;

	Drawing::Size size = get_ClientSize();
	size.Height -= _titleBar->get_Size().Height;
	int max = _array.front();
	for (size_t i = 1; i < _array.size(); ++i)
	{
		if (max < _array[i])
			max = _array[i];
	}

	int unitWidth = size.Width / _array.size();
	int unitHeight = size.Height / max;

	Graphics& g = e->Graphics;
	for (size_t i = 0; i < _array.size(); ++i)
	{
		SolidBrush brush(_color[i]);
		g.FillRectangle(brush, i * unitWidth + 5, 
			size.Height - _array[i] * unitHeight + _titleBar->get_Size().Height, 
			unitWidth - 10, _array[i] * unitHeight);
	}
}

void VisualSortForm::set_Fixed( size_t i )
{
	_color.at(i) = Color::Red;
}

void VisualSortForm::Swap( size_t a, size_t b )
{
	if (get_InvokeRequired())
		Invoke(Delegate<>(this, &VisualSortForm::Swap, a, b));
	else
		swap(_array.at(a), _array.at(b));
}

void VisualSortForm::BeginSort( vector<int>& array )
{
	_array = array;
	_color.clear();
	_color.resize(_array.size(), Color::Grey);
	if (_worker != NULL)
		_worker->Join();
	delete _worker;
	_worker = new Thread(ThreadStart(this, &VisualSortForm::Sort, _array));
	_worker->Start();
}

void VisualSortForm::Dispose()
{
	if (_worker == NULL)
		return;

	while (!_worker->Join(100))
	{
		Application::DoEvents();
	}

	delete _worker;
	_worker = NULL;
}
