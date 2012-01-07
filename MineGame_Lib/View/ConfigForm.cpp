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
	set_Size(Size(200, 300));

	_d->widthLabel.Show();
	Controls.Add(_d->widthLabel);
	_d->widthLabel.set_Text(L"Width:");
	_d->widthLabel.set_AutoSize(true);

	_d->heightLabel.Show();
	Controls.Add(_d->heightLabel);
	_d->heightLabel.set_Text(L"Height:");
	_d->heightLabel.set_AutoSize(true);
	_d->heightLabel.set_Height(_d->widthLabel.get_Height() + 10);

	_d->mineTotalLabel.Show();
	Controls.Add(_d->mineTotalLabel);
	_d->mineTotalLabel.set_Text(L"Mines:");
	_d->mineTotalLabel.set_AutoSize(true);
	_d->mineTotalLabel.set_Height(_d->heightLabel.get_Height() + 10);
}

