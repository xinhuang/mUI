#include "VisualSortForm.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
using std::swap;

using namespace mUI::System;

VisualSortForm::VisualSortForm(void)
{
	set_Size(Drawing::Size(500, 400));
	set_Location(Point(100, 100));

	Paint += EventHandler<PaintEventArgs*>(this, &VisualSortForm::OnPaint);
}

VisualSortForm::~VisualSortForm(void)
{
	Dispose();

}

void VisualSortForm::OnPaint( void* sender, PaintEventArgs* e )
{
	if (array_.size() == 0)
		return;

	Drawing::Size size = get_ClientSize();
	int max = array_.front();
	for (size_t i = 1; i < array_.size(); ++i)
	{
		if (max < array_[i])
			max = array_[i];
	}

	int unit_width = size.Width / array_.size();
	int unit_height = size.Height / max;

	Graphics& g = e->Graphics;
	for (size_t i = 0; i < array_.size(); ++i)
	{
		Brush brush(color_[i]);
		g.FillRectangle(brush, i * unit_width + 5, size.Height - array_[i] * unit_height, 
			unit_width - 10, array_[i] * unit_height);
	}
}

void VisualSortForm::set_Fixed( size_t i )
{
	color_.at(i) = Color::Red;
}

void VisualSortForm::Swap( size_t a, size_t b )
{
	if (InvokeRequired())
		BeginInvoke(Delegate<>(this, &VisualSortForm::Swap, a, b));
	else
		swap(array_.at(a), array_.at(b));
}

void VisualSortForm::BeginSort( vector<int>& array )
{
	array_ = array;
	color_.clear();
	color_.resize(array_.size(), Color::Grey);
	worker_.Join();
	worker_ = ThreadStart(this, &VisualSortForm::Sort, array_);
	worker_.Start();
}

void VisualSortForm::Dispose()
{
	while (!worker_.Join(100))
	{
		Application::DoEvents();
	}
}
