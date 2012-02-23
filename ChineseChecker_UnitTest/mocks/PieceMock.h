#ifndef __PIECEMOCK_H__
#define __PIECEMOCK_H__

#include <gmock/gmock.h>
#include <Presenter/Piece.h>

class PieceMock : public Piece
{
public:
	PieceMock() : Piece(-1) {}

	MOCK_CONST_METHOD0(get_Square, const Square*());
	MOCK_METHOD0(get_Square, Square*());
	MOCK_METHOD1(MoveTo, bool(Square*));
	MOCK_CONST_METHOD0(get_Id, int());
};

#endif // __PIECEMOCK_H__
