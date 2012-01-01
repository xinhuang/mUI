#ifndef __CONTROLMOCK_H__
#define __CONTROLMOCK_H__

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;

#include <gmock/gmock.h>

class ControlMock : public Control
{
public:
	MOCK_METHOD1(OnLayout, void(LayoutEventArgs*));
};

#endif // __CONTROLMOCK_H__
