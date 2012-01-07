#ifndef __MGAMEMOCK_H__
#define __MGAMEMOCK_H__

#include <gmock/gmock.h>

#include "ViewMock.h"

#include <Presenter/MGame.h>

class MGameMock : public MGame
{
public:
    MGameMock(View* view) : MGame(view) {}

	MOCK_METHOD0(Lose, void());
	MOCK_CONST_METHOD0(IsLost, bool());
	MOCK_METHOD0(IncFlagCount, void());
	MOCK_METHOD0(DecFlagCount, void());
};

#endif // __MGAMEMOCK_H__
