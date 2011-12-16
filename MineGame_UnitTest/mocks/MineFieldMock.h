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

	MOCK_METHOD1(UncoverAdjacent, void(const Point&));
	MOCK_CONST_METHOD1(get_AdjacentMineTotal, int(const Point&));
};

#endif // __MINEFIELDMOCK_H__
