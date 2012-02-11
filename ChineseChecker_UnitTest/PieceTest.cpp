#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include "mocks/PieceMock.h"
#include "mocks/SquareMock.h"

#include <Presenter/Piece.h>

class PieceTest : public ::testing::Test
{
public:
};

TEST_F(PieceTest, Constructor_Typical)
{
	Piece* sut = new Piece();

	ASSERT_NE(nullptr, sut);

	delete sut;
}

