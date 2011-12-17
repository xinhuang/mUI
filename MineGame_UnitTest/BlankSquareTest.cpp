#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/BlankSquare.h>

#include "mocks/MineFieldMock.h"
#include "mocks/ViewMock.h"
#include "mocks/SquareViewMock.h"

class BlankSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_view = new ViewMock();
		_game = new MGame(_view);
	}

	void TearDown()
	{
		delete _view;
		delete _game;
	}

protected:
	MGame* _game;
	View* _view;
};

TEST_F(BlankSquareTest, Constructor_Typical)
{
	BlankSquare* sut = new BlankSquare(NULL, NULL, 0, 0);

	ASSERT_TRUE(NULL != sut);
	ASSERT_EQ(SquareState::Covered, sut->get_State());
	delete sut;
}

TEST_F(BlankSquareTest, Uncover_Typical)
{
	MineFieldMock mineField;
	SquareViewMock squareViewMock;
	BlankSquare sut(_game, &mineField, 0, 0);
	sut.Bind(&squareViewMock);
	EXPECT_CALL(mineField, UncoverAdjacent(_)).Times(1);
	EXPECT_CALL(squareViewMock, set_State(SquareViewState::Blank)).Times(1);

	sut.Uncover();

	ASSERT_EQ(SquareState::Uncovered, sut.get_State());
}
