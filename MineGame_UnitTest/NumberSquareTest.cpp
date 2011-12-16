#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include <mUI.h>
using namespace mUI::System;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/NumberSquare.h>

#include "mocks/MineFieldMock.h"
#include "mocks/ViewMock.h"
#include "mocks/SquareViewMock.h"

class NumberSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_view = new ViewMock();
		_game = new MGame(_view);
		_mineField = new MineFieldMock();
		_sut = new NumberSquare(_game, _mineField, 0, 0);
		_squareView = new SquareViewMock();
	}

	void TearDown()
	{
		delete _game;
		delete _mineField;
		delete _view;
		delete _sut;
		delete _squareView;
	}

protected:
	NumberSquare* _sut;
	MGame* _game;
	MineFieldMock* _mineField;
	View* _view;
	SquareViewMock* _squareView;
};

TEST_F(NumberSquareTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _sut);
	ASSERT_EQ(SquareState::Covered, _sut->get_State());
}

TEST_F(NumberSquareTest, Uncover_Typical)
{
	EXPECT_CALL(*_mineField, get_AdjacentMineTotal(_sut))
		.Times(1)
		.WillOnce(Return(3));
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Number3)).Times(1);
	_sut->Bind(_squareView);

	_sut->Uncover();

	ASSERT_EQ(SquareState::Uncovered, _sut->get_State());
}

TEST_F(NumberSquareTest, Uncover_WhenFlagged)
{
	_sut->ToggleFlag();

	_sut->Uncover();

	ASSERT_EQ(SquareState::Flagged, _sut->get_State());
}

TEST_F(NumberSquareTest, Uncover_WhenQuestionMark)
{
	_sut->ToggleFlag();
	_sut->ToggleFlag();

	_sut->Uncover();

	ASSERT_EQ(SquareState::Uncovered, _sut->get_State());
}

TEST_F(NumberSquareTest, get_Number_Typical)
{
	int arbitraryNeighborMineTotal = 3;
	EXPECT_CALL(*_mineField, get_AdjacentMineTotal(_sut))
		.Times(1)
		.WillOnce(Return(arbitraryNeighborMineTotal));

	ASSERT_EQ(arbitraryNeighborMineTotal, _sut->get_Number());
}
