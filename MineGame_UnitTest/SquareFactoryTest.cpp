#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <MGame.h>
#include <MineField.h>
#include <SquareFactory.h>
#include <ISquare.h>
#include <MineSquare.h>
#include <BlankSquare.h>
#include <NumberSquare.h>

#include "mocks/MineFieldMock.h"

class SquareFactoryTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		_factory = new SquareFactory();
	}

	virtual void TearDown()
	{
		delete _factory;
		_factory = NULL;
		for(size_t i = 0; i < _squares.size(); ++i)
			delete _squares[i];
		_squares.clear();
	}

protected:
	SquareFactory* _factory;
	vector<ISquare*> _squares;
};

TEST_F(SquareFactoryTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _factory);
}

TEST_F(SquareFactoryTest, CreateSquares_MineField1x1AllMine)
{
	MGame game;
	game.set_MineFieldWidth(1);
	game.set_MineFieldHeight(1);
	game.set_MineTotal(1);
	MineField mineField(&game);
	
	_squares = _factory->CreateSquares(&game, &mineField);

	ASSERT_EQ(1, _squares.size());
	ASSERT_EQ(0, _squares[0]->get_Row());
	ASSERT_EQ(0, _squares[0]->get_Column());
	MineSquare* square = dynamic_cast<MineSquare*>(_squares[0]);
	ASSERT_TRUE(NULL != square);
}


TEST_F(SquareFactoryTest, CreateSquares_MineField1x1NoMine)
{
	MGame game;
	game.set_MineFieldWidth(1);
	game.set_MineFieldHeight(1);
	game.set_MineTotal(0);
	MineField mineField(&game);
	
	_squares = _factory->CreateSquares(&game, &mineField);

	ASSERT_EQ(1, _squares.size());
	ASSERT_EQ(0, _squares[0]->get_Row());
	ASSERT_EQ(0, _squares[0]->get_Column());
	BlankSquare* square = dynamic_cast<BlankSquare*>(_squares[0]);
	ASSERT_TRUE(NULL != square);
}
