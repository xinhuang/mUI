#ifndef __MOCKFORM_H__
#define __MOCKFORM_H__

#include <gmock/gmock.h>

#include <mUI.h>
using namespace mUI::System::Forms;

struct MockForm : public Form
{
	MOCK_METHOD1(OnActivated, void(EventArgs*));
	MOCK_METHOD1(OnDeactivate, void(EventArgs*));
};

#endif // __MOCKFORM_H__
