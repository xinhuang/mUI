#include <gtest/gtest.h>
#include <mUI.h>

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/ISquare.h>

#include <mocks/ViewMock.h>

class MGameTest : public testing::Test
{
public:
	void SetUp()
	{
		_viewMock = new ViewMock();
		_game = new MGame(_viewMock);
	}

	void TearDown()
	{
		delete _game;
		_game = NULL;
	}

protected:
	MGame* _game;
	ViewMock* _viewMock;
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

	ASSERT_TRUE(_game->get_MineField() != NULL);
	ASSERT_EQ(arbitrarySize, _game->get_MineField()->get_Size());
	ASSERT_EQ(arbitraryMineTotal, _game->get_MineField()->get_MineTotal());
}

TEST_F(MGameTest, Uncover_OnMineSquare)
{
	_game->set_MineFieldWidth(1);
	_game->set_MineFieldHeight(1);
	_game->set_MineTotal(1);

}
