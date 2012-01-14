#ifndef __CONTROLMOCK_H__
#define __CONTROLMOCK_H__

#include <mUI.h>
using namespace mUI;
using namespace mUI::System;
using namespace mUI::System::Forms;

#include <gmock/gmock.h>

class MockControl : public Control
{
public:
	MOCK_METHOD1(OnLayout, void(LayoutEventArgs*));
	MOCK_METHOD1(OnEnter, void(EventArgs*));
	MOCK_METHOD1(OnGotFocus, void(EventArgs*));
	MOCK_METHOD1(OnLostFocus, void(EventArgs*));
	MOCK_METHOD1(OnLeave, void(EventArgs*));
	MOCK_METHOD1(OnValidating, void(EventArgs*));
	MOCK_METHOD1(OnValidated, void(EventArgs*));
};

#endif // __CONTROLMOCK_H__
