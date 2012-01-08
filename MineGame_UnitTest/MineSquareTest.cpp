#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/MineSquare.h>

#include "mocks/MGameMock.h"
#include "mocks/SquareViewMock.h"

class MineSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_sut = new MineSquare(null, null, 
			ABITRARY_X, ABITRARY_Y);
	}

	void TearDown()
	{
		delete _sut;
	}

protected:
	MineSquare* _sut;
	static const int ABITRARY_Y = 27, ABITRARY_X = 43;
};

TEST_F(MineSquareTest, Constructor_Typical)
{
	ASSERT_TRUE(null != _sut);
	ASSERT_EQ(SquareState::Covered, _sut->get_State());
}

TEST_F(MineSquareTest, Uncover_Typical)
{
    ViewMock view;
    MGameMock game(&view);
    MineSquare mineSquare(&game, null, 0, 0);
    SquareViewMock squareView;
    mineSquare.Bind(&squareView);
    EXPECT_CALL(squareView, set_State(SquareViewState::Boomed)).Times(1);	
    EXPECT_CALL(game, Lose()).Times(1);

    mineSquare.Uncover();

    ASSERT_EQ(SquareState::Boomed, mineSquare.get_State());
}

TEST_F(MineSquareTest, Uncover_WhenMultipleTimes)
{
    ViewMock view;
    MGameMock game(&view);
    MineSquare mineSquare(&game, null, 0, 0);
    SquareViewMock squareView;
    mineSquare.Bind(&squareView);
    EXPECT_CALL(squareView, set_State(SquareViewState::Boomed)).Times(1);	
    EXPECT_CALL(game, Lose()).Times(1);

    mineSquare.Uncover();
    mineSquare.Uncover();

    ASSERT_EQ(SquareState::Boomed, mineSquare.get_State());
}

TEST_F(MineSquareTest, HasMine_Typical)
{
	ASSERT_TRUE(_sut->HasMine());
}

