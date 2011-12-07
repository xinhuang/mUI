#include <gtest/gtest.h>
#include <mUI.h>

#define private public
#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/ISquare.h>
#undef private

class MGameTest : public testing::Test
{
public:
	void SetUp()
	{
		_game = new MGame();
	}

	void TearDown()
	{
		delete _game;
		_game = NULL;
	}

protected:
	MGame* _game;
};

TEST_F(MGameTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _game);
}

TEST_F(MGameTest, NewGame_Typical)
{
	Size arbitrarySize(30, 20);
	int arbitraryMineTotal = 28;
	_game->set_MineFieldWidth(arbitrarySize.Width);
	_game->set_MineFieldHeight(arbitrarySize.Height);
	_game->set_MineTotal(arbitraryMineTotal);

	_game->NewGame();

	ASSERT_TRUE(_game->_mineField != NULL);
	ASSERT_EQ(arbitrarySize, _game->_mineField->get_Size());
	ASSERT_EQ(arbitraryMineTotal, _game->_mineField->get_MineTotal());
}

TEST_F(MGameTest, Uncover_OnMineSquare)
{

}
