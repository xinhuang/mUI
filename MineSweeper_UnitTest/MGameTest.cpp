#include <MGame.h>
#include <gtest\gtest.h>

class MGameTest : public testing::Test
{
};

TEST_F(MGameTest, Constructor_Typical)
{
	MGame* game = new MGame();
	ASSERT_TRUE(NULL != game);
	delete game;
}

