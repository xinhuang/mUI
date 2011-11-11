#include "MainFrame.h"

#include "PHGE.h"
#include "MovingForm.h"
#include "InfoForm.h"

MainFrame::MainFrame()
{
	set_Text(L"mUI Example - Moving Window");
}

int MainFrame::get_Fps() const
{
	return HGEFPS_UNLIMITED;
}

bool MainFrame::Initialize()
{
	KeyPress += KeyPressEventHandler(this, &MainFrame::MainFrame_OnKeyPress);

	infoform_ = new InfoForm();
	infoform_->set_Location(Point(0, 0));
	infoform_->Show();

	return true;
}

void MainFrame::MainFrame_OnKeyPress( void* sender, KeyPressEventArgs* e )
{
	switch (e->KeyChar)
	{
	case 'a':
		{
			e->Handled = true;
			AddForm();
		}
		break;

	case 'b':
		{
			e->Handled = true;
			RemoveForm();
		}
		break;
	}
}

bool MainFrame::LogicTick( float delta )
{
	PHGE hge;
	int sw = hge->System_GetState(HGE_SCREENWIDTH);
	int sh = hge->System_GetState(HGE_SCREENHEIGHT);
	for (size_t i = 0; i < forms_.size(); ++i)
	{
		MovingForm& form = *forms_[i];
		form.Move();
		if (form.get_Location().X < 0 
			|| form.get_Location().X + form.get_Size().Width > sw)
		{
			form.FlipHori();
		}
		if (form.get_Location().Y < 0 
			|| form.get_Location().Y + form.get_Size().Height > sh)
		{
			form.FlipVert();
		}
	}
	return false;
}

void MainFrame::RemoveForm()
{
	if (forms_.size() > 0)
	{
		Form* f = forms_.back();
		forms_.pop_back();
		f->Hide();
		delete f;
		infoform_->set_FormNumber(forms_.size());
	}
}

void MainFrame::AddForm()
{
	MovingForm* form = new MovingForm();
	PHGE hge;
	int sw = hge->System_GetState(HGE_SCREENWIDTH);
	int sh = hge->System_GetState(HGE_SCREENHEIGHT);

	Random random;
	Point loc;
	loc.X = random.Next(20, sw - form->get_Size().Width - 20);
	loc.Y = random.Next(20, sh - form->get_Size().Height - 20);
	form->set_Location(loc);
	form->Show();
	forms_.push_back(form);
	infoform_->set_FormNumber(forms_.size());
}
