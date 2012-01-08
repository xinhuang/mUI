#include "ConfigForm.h"

struct ConfigForm::Data
{
	Label widthLabel;
	Label heightLabel;
	Label mineTotalLabel;
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

	Controls.Add(_d->heightLabel);
	_d->heightLabel.set_Text(L"Height:");
	_d->heightLabel.set_AutoSize(true);
	_d->heightLabel.set_Location(Point(0, _d->widthLabel.get_Height() + gap));

	Controls.Add(_d->mineTotalLabel);
	_d->mineTotalLabel.set_Text(L"Mines:");
	_d->mineTotalLabel.set_AutoSize(true);
	_d->mineTotalLabel.set_Location(Point(0, _d->heightLabel.get_Top() + _d->heightLabel.get_Height() + gap));
}
