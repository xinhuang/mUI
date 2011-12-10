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

};

#endif // __MGAMEMOCK_H__
