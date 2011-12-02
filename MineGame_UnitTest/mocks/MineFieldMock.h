#ifndef __MINEFIELDMOCK_H__
#define __MINEFIELDMOCK_H__

#include <gmock/gmock.h>

#include <Presenter/ISquare.h>
#include <Presenter/MineField.h>

class SquareFactory;

class MineFieldMock : public MineField
{
	typedef MineField base;
public:
	MineFieldMock();

	MOCK_METHOD1(UncoverNeighborSquares, void(const ISquare&));
	MOCK_CONST_METHOD1(get_NeighborMineTotal, int(const ISquare*));
};

#endif // __MINEFIELDMOCK_H__
