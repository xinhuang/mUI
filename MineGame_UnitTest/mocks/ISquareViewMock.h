#ifndef __MGAMEMOCK_H__
#define __MGAMEMOCK_H__

#include <gmock/gmock.h>

#include <Presenter/ISquare.h>
#include <View/View.h>

class ISquareViewMock : public ISquareView
{
public:
	MOCK_METHOD1(set_State, void(SquareState::Enum));
	MOCK_CONST_METHOD0(get_Location, const Point&());
};

#endif // __MGAMEMOCK_H__
