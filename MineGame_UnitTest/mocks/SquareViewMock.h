#ifndef __SQUAREVIEWMOCK_H__
#define __SQUAREVIEWMOCK_H__

#include <gmock/gmock.h>

#include <View/View.h>

class SquareViewMock : public ISquareView
{
public:
	MOCK_METHOD1(set_State, void(SquareState::Enum));
	MOCK_METHOD1(set_Number, void(int));
	MOCK_CONST_METHOD0(get_Location, const Point&());
};

#endif // __SQUAREVIEWMOCK_H__
