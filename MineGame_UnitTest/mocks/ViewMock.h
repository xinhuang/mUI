#ifndef __VIEWMOCK_H__
#define __VIEWMOCK_H__

#include <gmock/gmock.h>

#include <View/View.h>

class ViewMock : public View
{
public:
	MOCK_METHOD2(set_SquareState, void(const Point& location, SquareState::Enum state));
	MOCK_METHOD1(set_RemainingMineTotal, void(int));
};

#endif // __VIEWMOCK_H__
