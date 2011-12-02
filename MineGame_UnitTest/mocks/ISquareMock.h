#ifndef __MGAMEMOCK_H__
#define __MGAMEMOCK_H__

#include <gmock/gmock.h>

#include <Presenter/ISquare.h>

class ISquareMock : public ISquare
{
public:
	MOCK_METHOD0(get_State, SquareState::Enum());
	MOCK_METHOD0(Uncover, void());
	MOCK_METHOD0(ToggleFlag, void());
};

#endif // __MGAMEMOCK_H__
