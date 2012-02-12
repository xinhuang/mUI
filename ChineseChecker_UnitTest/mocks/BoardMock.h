#ifndef __BOARDMOCK_H__
#define __BOARDMOCK_H__

#include <Presenter/Board.h>
#include <gmock/gmock.h>

class BoardMock : public Board
{
public:
	MOCK_CONST_METHOD1(GetSquaresInFormation, vector<Square*>(const Point& topLocation));
};

#endif // __BOARDMOCK_H__
