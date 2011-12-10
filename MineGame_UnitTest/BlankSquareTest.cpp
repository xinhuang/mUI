#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/BlankSquare.h>

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

// TODO: (BlankSquareTest, Uncover_Typical)
//TEST_F(BlankSquareTest, Uncover_Typical)
//{
//	MineFieldMock mineField;
//	BlankSquare blankSquare(NULL, &mineField, 0, 0);
//
//	EXPECT_CALL(mineField, UncoverNeighborSquares(_)).Times(1);
//
//	blankSquare.Uncover();
//}
