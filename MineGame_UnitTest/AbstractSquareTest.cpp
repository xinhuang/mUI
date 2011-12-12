#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <mUI.h>

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/AbstractSquare.h>

#include "mocks/SquareViewMock.h"

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
		_abstractSquare = new AbstractSquareFake(NULL, NULL, 
			ABITRARY_X, ABITRARY_Y);
		_view = new SquareViewMock();
	}

	void TearDown()
	{
		delete _abstractSquare;
		delete _view;
	}

protected:
	AbstractSquare* _abstractSquare;
	SquareViewMock* _view;

	static const int ABITRARY_Y = 27, ABITRARY_X = 43;
};

TEST_F(AbstractSquareTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _abstractSquare);
	ASSERT_EQ(SquareState::Covered, _abstractSquare->get_State());
	ASSERT_EQ(ABITRARY_Y, _abstractSquare->get_Y());
	ASSERT_EQ(ABITRARY_X, _abstractSquare->get_X());
	ASSERT_EQ(Point(ABITRARY_X, ABITRARY_Y), _abstractSquare->get_Location());
}

TEST_F(AbstractSquareTest, ToggleFlag_Once)
{
	_abstractSquare->ToggleFlag();
	
	ASSERT_EQ(SquareState::Flagged, _abstractSquare->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_Twice)
{
	_abstractSquare->ToggleFlag();
	_abstractSquare->ToggleFlag();
	
	ASSERT_EQ(SquareState::QuestionMark, _abstractSquare->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_ThreeTimes)
{
	_abstractSquare->ToggleFlag();
	_abstractSquare->ToggleFlag();
	_abstractSquare->ToggleFlag();
	
	ASSERT_EQ(SquareState::Uncovered, _abstractSquare->get_State());
}

TEST_F(AbstractSquareTest, HasMine_Typical)
{
	ASSERT_FALSE(_abstractSquare->HasMine());
}

TEST_F(AbstractSquareTest, SetState_Typical)
{
	_abstractSquare->Bind(_view);
	EXPECT_CALL(*_view, set_State(SquareState::Uncovered)).Times(1);

	static_cast<AbstractSquareFake*>(_abstractSquare)->
		set_State(SquareState::Uncovered);
}
