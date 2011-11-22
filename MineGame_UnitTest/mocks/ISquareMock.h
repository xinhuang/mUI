#ifndef __MGAMEMOCK_H__
#define __MGAMEMOCK_H__

#include <ISquare.h>
#include <gmock/gmock.h>

class ISquareMock : public ISquare
{
public:
	MOCK_METHOD0(get_State, SquareState::Enum());
	MOCK_METHOD0(Uncover, void());
	MOCK_METHOD0(ToggleFlag, void());
};

#endif // __MGAMEMOCK_H__
