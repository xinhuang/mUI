#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/BlankSquare.h>

#include "mocks/MineFieldMock.h"
#include "mocks/SquareViewMock.h"

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

TEST_F(BlankSquareTest, Uncover_Typical)
{
	MineFieldMock mineField;
	SquareViewMock squareViewMock;
	BlankSquare blankSquare(NULL, &mineField, 0, 0);
	blankSquare.Bind(&squareViewMock);
	EXPECT_CALL(mineField, UncoverAdjacent(_)).Times(1);
	EXPECT_CALL(squareViewMock, set_State(SquareState::Uncovered)).Times(1);

	blankSquare.Uncover();
}
