#ifndef __PIECEGROUPMOCK_H__
#define __PIECEGROUPMOCK_H__

#include <Presenter/PieceGroup.h>
#include <gmock/gmock.h>

class PieceGroupMock : public PieceGroup
{
public:
	PieceGroupMock() : PieceGroup(-1, nullptr, Point::Empty, Point::Empty) {}

	MOCK_METHOD0(Reset, void());
};

#endif // __PIECEGROUPMOCK_H__
