#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#define protected public
#	include <MGame.h>
#	include <MineField.h>
#	include <NumberSquare.h>
#undef protected
#undef private

using namespace mUI::System;

class NumberSquareTest : public testing::Test
{
public:
	void SetUp()
	{
		_game = new MGame();
		_mineField = new MineField(_game);
	}

	void TearDown()
	{
		delete _game;
		delete _mineField;
	}

protected:
	MGame* _game;
	MineField* _mineField;
};

TEST_F(NumberSquareTest, Constructor_Typical)
{
	NumberSquare* numberSquare = new NumberSquare(_game, _mineField, 0, 0, 2);

	ASSERT_TRUE(NULL != numberSquare);
	ASSERT_EQ(SquareState::Covered, numberSquare->get_State());
	ASSERT_EQ(2, numberSquare->get_NeighborMineTotal());

	delete numberSquare;
}

TEST_F(NumberSquareTest, Constructor_NeighborMineTotalTooBig)
{
	try
	{
		NumberSquare* numberSquare = new NumberSquare(_game, _mineField, 0, 0, 9);
		ASSERT_TRUE(false);
	}
	catch(const ArgumentException&)
	{
	}
}

TEST_F(NumberSquareTest, Constructor_NeighborMineTotalTooSmall)
{
	try
	{
		NumberSquare* numberSquare = new NumberSquare(_game, _mineField, 0, 0, 0);
		ASSERT_TRUE(false);
	}
	catch(const ArgumentException&)
	{
	}
}

TEST_F(NumberSquareTest, Uncover_Typical)
{
	NumberSquare numberSquare(NULL, NULL, 0, 0, 2);

	numberSquare.Uncover();

	ASSERT_EQ(SquareState::Uncovered, numberSquare.get_State());
}

TEST_F(NumberSquareTest, Uncover_WhenFlagged)
{
	NumberSquare numberSquare(NULL, NULL, 0, 0, 2);
	numberSquare.ToggleFlag();

	numberSquare.Uncover();

	ASSERT_EQ(SquareState::Flagged, numberSquare.get_State());
}

TEST_F(NumberSquareTest, Uncover_WhenQuestionMark)
{
	NumberSquare numberSquare(NULL, NULL, 0, 0, 2);
	numberSquare.ToggleFlag();
	numberSquare.ToggleFlag();

	numberSquare.Uncover();

	ASSERT_EQ(SquareState::Uncovered, numberSquare.get_State());
}
