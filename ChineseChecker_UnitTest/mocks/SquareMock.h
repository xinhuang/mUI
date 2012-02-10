#ifndef __SQUAREMOCK_H__
#define __SQUAREMOCK_H__

#include <gmock/gmock.h>
#include <Presenter/Square.h>

class SquareMock : public Square
{
public:
	SquareMock() : Square(Point::Empty) {}

	MOCK_METHOD1(set_Piece, void(Piece*));
};

#endif // __SQUAREMOCK_H__
