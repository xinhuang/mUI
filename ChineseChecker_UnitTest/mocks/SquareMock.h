#ifndef __SQUAREMOCK_H__
#define __SQUAREMOCK_H__

#include <gmock/gmock.h>
#include <Presenter/Square.h>

class SquareMock : public Square
{
public:
	SquareMock() : Square(nullptr, Point::Empty) {}

	MOCK_METHOD1(set_Piece, void(Piece*));
	MOCK_METHOD0(get_Piece, Piece*());

	MOCK_CONST_METHOD0(get_Location, const Point&());
};

#endif // __SQUAREMOCK_H__
