#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <ISquare.h>
#include <NumberSquare.h>
#undef private

class NumberSquareTest : public testing::Test
{
public:
};

TEST_F(NumberSquareTest, Constructor_Typical)
{
	NumberSquare* numberSquare = new NumberSquare();
	ASSERT_TRUE(NULL != numberSquare);
	ASSERT_EQ(SquareState::Covered, numberSquare->get_State());
	delete numberSquare;
}

