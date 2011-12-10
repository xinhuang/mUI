#ifndef __VIEWMOCK_H__
#define __VIEWMOCK_H__

#include <gmock/gmock.h>

#include <View/View.h>

class ViewMock : public View
{
public:
	MOCK_METHOD3(set_SquareState, void(const Point& location, SquareState::Enum state, IntPtr param));
	MOCK_METHOD1(set_RemainingMineTotal, void(int));
    MOCK_METHOD1(CreateSquares, void(const Size&));
};

#endif // __VIEWMOCK_H__
