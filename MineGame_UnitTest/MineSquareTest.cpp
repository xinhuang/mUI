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
	void SetUp()
	{
		_mineSquare = new MineSquare(NULL, NULL, 
			ABITRARY_ROW, ABITRARY_COLUMN);
	}

	void TearDown()
	{
		delete _mineSquare;
	}

protected:
	MineSquare* _mineSquare;
	static const int ABITRARY_ROW = 27, ABITRARY_COLUMN = 43;
};

TEST_F(MineSquareTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _mineSquare);
	ASSERT_EQ(SquareState::Covered, _mineSquare->get_State());
}

TEST_F(MineSquareTest, Uncover_Typical)
{
	MGameMock game;
	MineSquare mineSquare(&game, NULL, 0, 0);
	
	EXPECT_CALL(game, Lose()).Times(1);

	mineSquare.Uncover();

	ASSERT_EQ(SquareState::Boomed, mineSquare.get_State());
}

TEST_F(MineSquareTest, HasMine_Typical)
{
	ASSERT_TRUE(_mineSquare->HasMine());
}

