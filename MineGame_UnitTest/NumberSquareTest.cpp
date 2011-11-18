#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <ISquare.h>
#include <NumberSquare.h>
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

