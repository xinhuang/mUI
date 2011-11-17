#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#undef private

class MGameTest : public testing::Test
{
public:
	void SetUp()
	{
		_Game = new MGame();
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
