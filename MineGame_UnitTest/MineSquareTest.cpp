#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#define private public
#	include <MGame.h>
#	include <MineField.h>
#	include <MineSquare.h>
#undef private

#include "mocks/MGameMock.h"

class MineSquareTest : public testing::Test
{
public:
};

TEST_F(MineSquareTest, Constructor_Typical)
{
	MineSquare* mineSquare = new MineSquare(NULL, NULL, 0, 0);

	ASSERT_TRUE(NULL != mineSquare);
	ASSERT_EQ(SquareState::Covered, mineSquare->get_State());
	delete mineSquare;
}

TEST_F(MineSquareTest, Uncover_Typical)
{
	MGameMock game;
	MineSquare mineSquare(&game, NULL, 0, 0);
	
	EXPECT_CALL(game, Lose()).Times(1);

	mineSquare.Uncover();

	ASSERT_EQ(SquareState::Boomed, mineSquare.get_State());
}

