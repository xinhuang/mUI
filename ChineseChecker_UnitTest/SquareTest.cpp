#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include "mocks/PieceMock.h"
#include "mocks/SquareMock.h"

#include <Presenter/Square.h>

class SquareTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = new Square(Point::Empty);
		_pieceMock = new PieceMock();
	}

	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
		delete _pieceMock;
	}

protected:
	PieceMock* _pieceMock;
	Square* _sut;
};

TEST_F(SquareTest, Constructor_Typical)
{
	ASSERT_TRUE(nullptr != _sut);
}

TEST_F(SquareTest, get_Piece_WhenDefault)
{
	ASSERT_TRUE(nullptr == _sut->get_Piece());
}
