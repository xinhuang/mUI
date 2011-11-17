#include <gtest\gtest.h>
#include <mUI.h>

#define private public
#include <MGame.h>
#include <MineField.h>
#include <ISquare.h>
#undef private

class MineFieldTest : public testing::Test
{
public:
	void SetUp()
	{
		_game = new MGame();
		_game->set_MineFieldHeight(_arbitraryHeight);
		_game->set_MineFieldWidth(_arbitraryWidth);
		_game->set_MineTotal(_arbitraryMineTotal);
		_mineField = new MineField(_game);
	}
	void TearDown()
	{
		delete _mineField;
		delete _game;
	}

protected:
	static const int _arbitraryMineTotal = 20;
	static const int _arbitraryHeight = 20;
	static const int _arbitraryWidth = 20;
	MGame* _game;
	MineField* _mineField;
};

TEST_F(MineFieldTest, Constructor_Typical)
{
	MineField* mineField = new MineField(_game);

	ASSERT_TRUE(NULL != mineField);
	delete mineField;
}

TEST_F(MineFieldTest, Size_Typical)
{
	ASSERT_EQ(_game->get_MineFieldSize(), _mineField->get_Size());
}

TEST_F(MineFieldTest, MineTotal_Typical)
{
	ASSERT_EQ(_game->get_MineTotal(), _mineField->get_MineTotal());
}
