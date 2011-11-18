#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#define private public
#include <MGame.h>
#include <MineField.h>
#include <BlankSquare.h>
#undef private

#include "mocks/MineFieldMock.h"

class BlankSquareTest : public testing::Test
{
public:
};

TEST_F(BlankSquareTest, Constructor_Typical)
{
	BlankSquare* blankSquare = new BlankSquare(NULL, NULL, 0, 0);

	ASSERT_TRUE(NULL != blankSquare);
	ASSERT_EQ(SquareState::Covered, blankSquare->get_State());
	delete blankSquare;
}

TEST_F(BlankSquareTest, Uncover_Typical)
{
	MineFieldMock mineField;
	BlankSquare blankSquare(NULL, &mineField, 0, 0);
	EXPECT_CALL(mineField, UncoverNeighborSquares(_)).Times(1);

	blankSquare.Uncover();

	//ASSERT_EQ(true, _mineFieldFake);
}
