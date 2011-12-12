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
		_sut = new AbstractSquareFake(NULL, NULL, 
			ABITRARY_X, ABITRARY_Y);
		_view = new SquareViewMock();
	}

	void TearDown()
	{
		delete _sut;
		delete _view;
	}

protected:
	AbstractSquare* _sut;
	SquareViewMock* _view;

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
	_sut->ToggleFlag();
	
	ASSERT_EQ(SquareState::Flagged, _sut->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_Twice)
{
	_sut->ToggleFlag();
	_sut->ToggleFlag();
	
	ASSERT_EQ(SquareState::QuestionMark, _sut->get_State());
}

TEST_F(AbstractSquareTest, ToggleFlag_ThreeTimes)
{
	_sut->ToggleFlag();
	_sut->ToggleFlag();
	_sut->ToggleFlag();
	
	ASSERT_EQ(SquareState::Uncovered, _sut->get_State());
}

TEST_F(AbstractSquareTest, HasMine_Typical)
{
	ASSERT_FALSE(_sut->HasMine());
}

TEST_F(AbstractSquareTest, SetState_Typical)
{
	_sut->Bind(_view);
	EXPECT_CALL(*_view, set_State(SquareState::Uncovered)).Times(1);

	static_cast<AbstractSquareFake*>(_sut)->
		set_State(SquareState::Uncovered);
}
