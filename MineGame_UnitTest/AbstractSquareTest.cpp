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
		: base(game, mineField, row, column)
	{
	}
};

class AbstractSquareTest : public testing::Test
{
public:

protected:
};

TEST_F(AbstractSquareTest, Constructor_Typical)
{
	int arbitraryRow = 27, arbitraryColumn = 43;
	AbstractSquare* abstractSquare = new AbstractSquareFake(NULL, NULL, 
											arbitraryRow, arbitraryColumn);

	ASSERT_TRUE(NULL != abstractSquare);
	ASSERT_EQ(SquareState::Covered, abstractSquare->get_State());
	ASSERT_EQ(arbitraryRow, abstractSquare->get_Row());
	ASSERT_EQ(arbitraryColumn, abstractSquare->get_Column());

	delete abstractSquare;
}
