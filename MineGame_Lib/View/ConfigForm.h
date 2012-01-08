#ifndef __CONFIGFORM_H__
#define __CONFIGFORM_H__

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;

class ConfigForm : public Form
{
public:
	ConfigForm();
	virtual ~ConfigForm();

protected:
	void InitializeComponents();

private:
	struct Data;
	Data* _d;
};

#endif // __CONFIGFORM_H__
