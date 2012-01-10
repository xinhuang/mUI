#include "ConfigForm.h"

struct ConfigForm::Data
{
	Label widthLabel;
	Label heightLabel;
	Label mineTotalLabel;
	TextBox widthTextBox;
};

ConfigForm::ConfigForm()
	: _d(new Data())
{
	InitializeComponents();
}

ConfigForm::~ConfigForm()
{
	delete _d;
}

void ConfigForm::InitializeComponents()
{
	set_Size(Size(100, 70));

	int gap = 3;

	Controls.Add(_d->widthLabel);
	_d->widthLabel.set_AutoSize(true);
	_d->widthLabel.set_Text(L"Width:");
    _d->widthLabel.set_AnchorStyles(AnchorStyles::Left);

	Controls.Add(_d->widthTextBox);
	_d->widthTextBox.set_Location(Point(_d->widthLabel.get_Right(), _d->widthLabel.get_Location().Y));
	_d->widthTextBox.set_Size(Size(get_Width() - _d->widthTextBox.get_Left() - 5, _d->widthLabel.get_Height()));
	_d->widthTextBox.set_AnchorStyles(AnchorStyles::LeftRight);
	_d->widthTextBox.set_BorderStyle(FormBorderStyle::FixedSingle);

	Controls.Add(_d->heightLabel);
	_d->heightLabel.set_Text(L"Height:");
	_d->heightLabel.set_AutoSize(true);
	_d->heightLabel.set_Location(Point(0, _d->widthLabel.get_Height() + gap));
    _d->heightLabel.set_AnchorStyles(AnchorStyles::Left);

	Controls.Add(_d->mineTotalLabel);
	_d->mineTotalLabel.set_Text(L"Mines:");
	_d->mineTotalLabel.set_AutoSize(true);
	_d->mineTotalLabel.set_Location(Point(0, _d->heightLabel.get_Top() + _d->heightLabel.get_Height() + gap));
    _d->mineTotalLabel.set_AnchorStyles(AnchorStyles::Left);
}
