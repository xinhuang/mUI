#ifndef __CGAMEMOCK_H__
#define __CGAMEMOCK_H__

#include <Presenter/CGame.h>
#include <gmock/gmock.h>

class CGameMock : public CGame
{
public:
	MOCK_METHOD0(get_Picked, Piece*());
	MOCK_METHOD1(set_Picked, void(Piece*));
};

#endif // __CGAMEMOCK_H__
