#ifndef __MGAMEMOCK_H__
#define __MGAMEMOCK_H__

#include <MGame.h>

class MGameMock : public MGame
{
public:
	MOCK_METHOD0(Lose, void());
};

#endif // __MGAMEMOCK_H__
