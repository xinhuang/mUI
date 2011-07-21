#include "VisualSortForm.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>
using std::swap;

using namespace mUI::System;

#include "TitleBar.h"

VisualSortForm::VisualSortForm(void) : worker_(NULL)
{
	set_Size(Drawing::Size(500, 400));
	set_Location(Point(100, 100));

	titlebar_ = new TitleBar();
	titlebar_->set_Size(Size(this->get_Size().Width - 2, 20));
	Controls.Add(*titlebar_);

	Paint += PaintEventHandler(this, &VisualSortForm::OnPaint);
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
	size.Height -= titlebar_->get_Size().Height;
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
		SolidBrush brush(color_[i]);
		g.FillRectangle(brush, i * unit_width + 5, 
			size.Height - array_[i] * unit_height + titlebar_->get_Size().Height, 
			unit_width - 10, array_[i] * unit_height);
	}
}

void VisualSortForm::set_Fixed( size_t i )
{
	color_.at(i) = Color::Red;
}

void VisualSortForm::Swap( size_t a, size_t b )
{
	if (get_InvokeRequired())
		Invoke(Delegate<>(this, &VisualSortForm::Swap, a, b));
	else
		swap(array_.at(a), array_.at(b));
}

void VisualSortForm::BeginSort( vector<int>& array )
{
	array_ = array;
	color_.clear();
	color_.resize(array_.size(), Color::Grey);
	if (worker_ != NULL)
		worker_->Join();
	delete worker_;
	worker_ = new Thread(ThreadStart(this, &VisualSortForm::Sort, array_));
	worker_->Start();
}

void VisualSortForm::Dispose()
{
	if (worker_ == NULL)
		return;

	while (!worker_->Join(100))
	{
		Application::DoEvents();
	}
}
