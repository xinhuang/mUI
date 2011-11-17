#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <ISquare.h>
#include <MineSquare.h>
#undef private

class MineSquareTest : public testing::Test
{
public:
};

TEST_F(MineSquareTest, Constructor_Typical)
{
	MGame* game = new MGame();

	MineSquare* mineSquare = new MineSquare(game);

	ASSERT_TRUE(NULL != mineSquare);
	ASSERT_EQ(SquareState::Covered, mineSquare->get_State());
	delete mineSquare;
	delete game;
}

