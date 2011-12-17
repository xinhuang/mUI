#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include <mUI.h>

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/AbstractSquare.h>

#include "mocks/SquareViewMock.h"
#include "mocks/ViewMock.h"
#include "mocks/MGameMock.h"

class AbstractSquareFake : public AbstractSquare
{
	typedef AbstractSquare base;

public:
	AbstractSquareFake(MGame* game, MineField* mineField, int row, int column)
		: base(game, mineField, Point(row, column))
	{
	}

	virtual void Uncover() {}

	using base::set_State;
};

class AbstractSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_view = new ViewMock();
		_game = new MGameMock(_view);
		_sut = new AbstractSquareFake(_game, NULL, 
			ABITRARY_X, ABITRARY_Y);
		_squareView = new SquareViewMock();
		_sut->Bind(_squareView);
	}

	void TearDown()
	{
		delete _sut;
		delete _squareView;
		delete _game;
		delete _view;
	}

protected:
	AbstractSquare* _sut;
	SquareViewMock* _squareView;
	MGameMock* _game;
	ViewMock* _view;

	static const int ABITRARY_Y = 27, ABITRARY_X = 43;
};

TEST_F(AbstractSquareTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _sut);
	ASSERT_EQ(SquareState::Covered, _sut->get_State());
	ASSERT_EQ(ABITRARY_Y, _sut->get_Y());
	ASSERT_EQ(ABITRARY_X, _sut->get_X());
	ASSERT_EQ(Point(ABITRARY_X, ABITRARY_Y), _sut->get_Location());
}

TEST_F(AbstractSquareTest, ToggleFlag_Once)
{
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Flagged)).Times(1);

	_sut->ToggleFlag();

	ASSERT_EQ(SquareState::Flagged, _sut->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_OnceWhenLost)
{
	EXPECT_CALL(*_game, IsLost()).Times(1).WillOnce(Return(true));

	_sut->ToggleFlag();

	ASSERT_EQ(SquareState::Covered, _sut->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_Twice)
{
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Flagged)).Times(1);
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Questioned)).Times(1);

	_sut->ToggleFlag();
	_sut->ToggleFlag();
	
	ASSERT_EQ(SquareState::Questioned, _sut->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_ThreeTimes)
{
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Flagged)).Times(1);
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Questioned)).Times(1);
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Covered)).Times(1);

	_sut->ToggleFlag();
	_sut->ToggleFlag();
	_sut->ToggleFlag();
	
	ASSERT_EQ(SquareState::Covered, _sut->get_State());
}

TEST_F(AbstractSquareTest, HasMine_Typical)
{
	ASSERT_FALSE(_sut->HasMine());
}

TEST_F(AbstractSquareTest, Bind_Typical)
{
	EXPECT_CALL(*_squareView, set_State(SquareViewState::Covered)).Times(1);

	_sut->Bind(_squareView);
}
