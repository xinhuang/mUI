#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <ISquare.h>
#undef private

class MGameTest : public testing::Test
{
public:
	void SetUp()
	{
		_Game = new MGame();
		Size arbitrarySize(30, 20);
		int arbitraryMineTotal = 28;
		_Game->set_MineFieldWidth(arbitrarySize.Width);
		_Game->set_MineFieldHeight(arbitrarySize.Height);
		_Game->set_MineTotal(arbitraryMineTotal);

		_Game->NewGame();
	}

	void TearDown()
	{
		delete _Game;
	}

protected:
	MGame* _Game;
};

TEST_F(MGameTest, Constructor_Typical)
{
	MGame* game = new MGame();

	ASSERT_TRUE(NULL != game);
	delete game;
}

TEST_F(MGameTest, NewGame_Typical)
{
	delete _Game;
	_Game = new MGame();
	Size arbitrarySize(30, 20);
	int arbitraryMineTotal = 28;
	_Game->set_MineFieldWidth(arbitrarySize.Width);
	_Game->set_MineFieldHeight(arbitrarySize.Height);
	_Game->set_MineTotal(arbitraryMineTotal);

	_Game->NewGame();

	ASSERT_TRUE(_Game->_MineField != NULL);
	ASSERT_EQ(arbitrarySize, _Game->_MineField->get_Size());
	ASSERT_EQ(arbitraryMineTotal, _Game->_MineField->get_MineTotal());
}

//TEST_F(MGameTest, Uncover_Typical)
//{
//	int arbitraryRowIndex = _Game->get_MineFieldSize().Width / 2;
//	int arbitraryColumnIndex = _Game->get_MineFieldSize().Height / 2;
//
//	_Game->Uncover(arbitraryRowIndex, arbitraryColumnIndex);
//
//	ISquare* square = _Game->_MineField->SquareAt(arbitraryRowIndex, arbitraryColumnIndex);
//	ASSERT_TRUE(NULL != square);
//	ASSERT_NE(SquareState::Uncovered, square->get_State());
//}
