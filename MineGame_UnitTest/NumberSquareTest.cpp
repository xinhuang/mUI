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
	}

	void TearDown()
	{
		delete _game;
	}

protected:
	MGame* _game;
};

TEST_F(NumberSquareTest, Constructor_Typical)
{
	MGame* game = new MGame();

	NumberSquare* numberSquare = new NumberSquare(game, 2);

	ASSERT_TRUE(NULL != numberSquare);
	ASSERT_EQ(SquareState::Covered, numberSquare->get_State());
	delete numberSquare;
	delete game;
}

TEST_F(NumberSquareTest, Constructor_NeighborMineTotalTooBig)
{
	try
	{
		NumberSquare* numberSquare = new NumberSquare(_game, 9);
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
		NumberSquare* numberSquare = new NumberSquare(_game, 0);
		ASSERT_TRUE(false);
	}
	catch(const ArgumentException&)
	{
	}
}

