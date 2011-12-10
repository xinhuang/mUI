#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/MineSquare.h>

#include "mocks/MGameMock.h"

class MineSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_mineSquare = new MineSquare(NULL, NULL, 
			ABITRARY_X, ABITRARY_Y);
	}

	void TearDown()
	{
		delete _mineSquare;
	}

protected:
	MineSquare* _mineSquare;
	static const int ABITRARY_Y = 27, ABITRARY_X = 43;
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

