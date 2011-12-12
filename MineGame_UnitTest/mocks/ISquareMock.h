#ifndef __ISQUAREMOCK_H__
#define __ISQUAREMOCK_H__

#include <gmock/gmock.h>

#include <Presenter/ISquare.h>
#include <View/View.h>

class ISquareMock : public ISquare
{
public:
	MOCK_CONST_METHOD0(get_State, SquareState::Enum());
	MOCK_CONST_METHOD0(get_X, int());
	MOCK_CONST_METHOD0(get_Y, int());
	MOCK_CONST_METHOD0(get_Location, const Point&());
	MOCK_CONST_METHOD0(HasMine, bool());
	MOCK_METHOD1(set_State, void(SquareState::Enum));
	MOCK_METHOD1(Bind, void(ISquareView*));
	MOCK_METHOD0(Uncover, void());
	MOCK_METHOD0(ToggleFlag, void());
};

#endif // __ISQUAREMOCK_H__
