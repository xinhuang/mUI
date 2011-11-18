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
	BlankSquare* blankSquare = new BlankSquare(NULL, NULL, 0, 0);

	ASSERT_TRUE(NULL != blankSquare);
	ASSERT_EQ(SquareState::Covered, blankSquare->get_State());
	delete blankSquare;
}

