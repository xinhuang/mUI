#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <AbstractSquare.h>
#undef private

class AbstractSquareFake : public AbstractSquare
{
	typedef AbstractSquare base;
public:
	AbstractSquareFake(MGame* game, MineField* mineField, int row, int column)
		: base(game, mineField, Point(row, column))
	{
	}
	virtual void Uncover() {}
};

class AbstractSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_abstractSquare = new AbstractSquareFake(NULL, NULL, 
			ABITRARY_ROW, ABITRARY_COLUMN);
	}

	void TearDown()
	{
		delete _abstractSquare;
	}

protected:
	AbstractSquare* _abstractSquare;
	static const int ABITRARY_ROW = 27, ABITRARY_COLUMN = 43;
};

TEST_F(AbstractSquareTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _abstractSquare);
	ASSERT_EQ(SquareState::Covered, _abstractSquare->get_State());
	ASSERT_EQ(ABITRARY_ROW, _abstractSquare->get_Row());
	ASSERT_EQ(ABITRARY_COLUMN, _abstractSquare->get_Column());
	ASSERT_EQ(Point(ABITRARY_ROW, ABITRARY_COLUMN), _abstractSquare->get_Location());
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
