#ifndef __MINEFIELDMOCK_H__
#define __MINEFIELDMOCK_H__

#include <MineField.h>
#include <gmock/gmock.h>

class MineFieldMock : public MineField
{
	typedef MineField base;
public:
	MineFieldMock() : base(NULL) {}

	MOCK_METHOD1(UncoverNeighborSquares, void(const ISquare&));

protected:
	virtual void CreateSquares() {}
};

#endif // __MINEFIELDMOCK_H__
