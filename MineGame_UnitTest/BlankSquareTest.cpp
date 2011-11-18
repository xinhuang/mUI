#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <BlankSquare.h>
#undef private

class BlankSquareTest : public testing::Test
{
public:
};

TEST_F(BlankSquareTest, Constructor_Typical)
{
	MGame* game = new MGame();

	BlankSquare* blankSquare = new BlankSquare(game);

	ASSERT_TRUE(NULL != blankSquare);
	ASSERT_EQ(SquareState::Covered, blankSquare->get_State());
	delete blankSquare;
	delete game;
}

