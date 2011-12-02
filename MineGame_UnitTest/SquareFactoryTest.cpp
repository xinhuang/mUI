#include <gtest/gtest.h>
#include <mUI.h>

#include <gmock/gmock.h>
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/SquareFactory.h>
#include <Presenter/MineSquare.h>
#include <Presenter/BlankSquare.h>
#include <Presenter/NumberSquare.h>

#include "mocks/MineFieldMock.h"

class SquareFactoryTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		_factory = new SquareFactory();
		_fieldMap.resize(9, false);
		_fieldSize = Size(3, 3);
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
	vector<bool> _fieldMap;
	static const int _middleSquareIndex = 4;
	Size _fieldSize;
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
	MineField& mineField(*game.get_MineField());
	
	_squares = _factory->CreateSquares(&game, &mineField);

	ASSERT_EQ(1, _squares.size());
	ASSERT_EQ(0, _squares[0]->get_Y());
	ASSERT_EQ(0, _squares[0]->get_X());
	MineSquare* square = dynamic_cast<MineSquare*>(_squares[0]);
	ASSERT_TRUE(NULL != square);
}

TEST_F(SquareFactoryTest, CreateSquares_MineField1x1NoMine)
{
	MGame game;
	game.set_MineFieldWidth(1);
	game.set_MineFieldHeight(1);
	game.set_MineTotal(0);
	MineField& mineField(*game.get_MineField());
	
	_squares = _factory->CreateSquares(&game, &mineField);

	ASSERT_EQ(1, _squares.size());
	ASSERT_EQ(0, _squares[0]->get_Y());
	ASSERT_EQ(0, _squares[0]->get_X());
	BlankSquare* square = dynamic_cast<BlankSquare*>(_squares[0]);
	ASSERT_TRUE(NULL != square);
}

TEST_F(SquareFactoryTest, GenerateMineFieldMap_MineField1x1MineTotal1)
{
	MGame game;
	game.set_MineFieldHeight(1);
	game.set_MineFieldWidth(1);
	game.set_MineTotal(1);
	MineField& mineField(*game.get_MineField());

	vector<bool> map = _factory->GenerateMineFieldMap(mineField.get_Size(), 
														mineField.get_MineTotal());

	ASSERT_EQ(1, map.size());
	ASSERT_EQ(true, map[0]);
}

TEST_F(SquareFactoryTest, GenerateMineFieldMap_MineField1x1MineTotal0)
{
	vector<bool> map = _factory->GenerateMineFieldMap(Size(1, 1), 0);

	ASSERT_EQ(1, map.size());
	ASSERT_EQ(false, map[0]);
}

TEST_F(SquareFactoryTest, GenerateMineFieldMap_MineField2x1MineTotal1)
{
	vector<bool> map = _factory->GenerateMineFieldMap(Size(2, 1), 1);

	ASSERT_EQ(2, map.size());
	ASSERT_NE(map[0], map[1]);
}

TEST_F(SquareFactoryTest, GenerateMineFieldMap_MultipleTimesMineField2x1MineTotal1)
{	
	vector<bool> firstMap = _factory->GenerateMineFieldMap(Size(2, 1), 1);
	for (int i = 0; i < 30; ++i)
	{
		vector<bool> map = _factory->GenerateMineFieldMap(Size(2, 1), 1);

		if (firstMap[0] != map[0])
			return;
	}

	ASSERT_TRUE(false);
}

TEST_F(SquareFactoryTest, CreateSquares_MineField2x1MineTotal1)
{
	MGame game;
	MineField& mineField(*game.get_MineField());
	mineField.set_Size(Size(2, 1));
	mineField.set_MineTotal(1);
	
	_squares = _factory->CreateSquares(&game, &mineField);

	NumberSquare* numberSquare = dynamic_cast<NumberSquare*>(_squares[0]);
	if (numberSquare == NULL)
		numberSquare = dynamic_cast<NumberSquare*>(_squares[1]);

	ASSERT_TRUE(NULL != numberSquare);
	ASSERT_EQ(1, numberSquare->get_Number());
}

TEST_F(SquareFactoryTest, CreateSquares_SameAsFieldMap)
{
	Size fieldSize(10, 10);
	int mineTotal = 35;
	MGame game;
	game.set_MineFieldHeight(fieldSize.Height);
	game.set_MineFieldWidth(fieldSize.Width);
	game.set_MineTotal(mineTotal);
	MineField& mineField(*game.get_MineField());
	vector<bool> fieldMap = _factory->GenerateMineFieldMap(fieldSize, mineTotal);

	_squares = _factory->CreateSquaresUsingFieldMap(&game, &mineField, fieldMap);

	ASSERT_EQ(fieldMap.size(), _squares.size());
	for (size_t i = 0; i < fieldMap.size(); ++i)
	{
		ASSERT_EQ(fieldMap[i], _squares[i]->HasMine());
	}
}

TEST_F(SquareFactoryTest, IsMineUp_WhenTrue)
{
	_fieldMap[1] = true;

	ASSERT_TRUE(_factory->IsMineUp(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineUp_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineUp(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineUp_WhenNoUpSquare)
{
	ASSERT_FALSE(_factory->IsMineUp(_fieldMap, _fieldSize, 1));
}

TEST_F(SquareFactoryTest, IsMineDown_WhenTrue)
{
	_fieldMap[7] = true;

	ASSERT_TRUE(_factory->IsMineDown(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineDown_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineDown(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineDown_WhenNoDownSquare)
{
	ASSERT_FALSE(_factory->IsMineDown(_fieldMap, _fieldSize, 7));
}

TEST_F(SquareFactoryTest, IsMineLeft_WhenTrue)
{
	_fieldMap[3] = true;

	ASSERT_TRUE(_factory->IsMineLeft(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineLeft_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineLeft(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineLeft_WhenNoLeftSquare)
{
	ASSERT_FALSE(_factory->IsMineLeft(_fieldMap, _fieldSize, 0));
}

TEST_F(SquareFactoryTest, IsMineRight_WhenTrue)
{
	_fieldMap[5] = true;

	ASSERT_TRUE(_factory->IsMineRight(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineRight_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineRight(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineRight_WhenNoRightSquare)
{
	ASSERT_FALSE(_factory->IsMineRight(_fieldMap, _fieldSize, 2));
}

TEST_F(SquareFactoryTest, IsMineUpRight_WhenTrue)
{
	_fieldMap[0] = true;

	ASSERT_TRUE(_factory->IsMineUpRight(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineUpRight_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineUpRight(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineUpRight_WhenNoUpRightSquare)
{
	ASSERT_FALSE(_factory->IsMineUpRight(_fieldMap, _fieldSize, 0));
}

TEST_F(SquareFactoryTest, IsMineUpLeft_WhenTrue)
{
	_fieldMap[2] = true;

	ASSERT_TRUE(_factory->IsMineUpLeft(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineUpLeft_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineUpLeft(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineUpLeft_WhenNoUpLeftSquare)
{
	ASSERT_FALSE(_factory->IsMineUpLeft(_fieldMap, _fieldSize, 2));
}

TEST_F(SquareFactoryTest, IsMineDownRight_WhenTrue)
{
	_fieldMap[8] = true;

	ASSERT_TRUE(_factory->IsMineDownRight(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineDownRight_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineDownRight(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineDownRight_WhenNoDownRightSquare)
{
	ASSERT_FALSE(_factory->IsMineDownRight(_fieldMap, _fieldSize, 8));
}

TEST_F(SquareFactoryTest, IsMineDownLeft_WhenTrue)
{
	_fieldMap[6] = true;

	ASSERT_TRUE(_factory->IsMineDownLeft(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineDownLeft_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMineDownLeft(_fieldMap, _fieldSize, _middleSquareIndex));
}

TEST_F(SquareFactoryTest, IsMineDownLeft_WhenNoDownLeftSquare)
{
	ASSERT_FALSE(_factory->IsMineDownLeft(_fieldMap, _fieldSize, 6));
}

TEST_F(SquareFactoryTest, IsMine_WhenTrue)
{
	_fieldMap[2] = true;

	ASSERT_TRUE(_factory->IsMine(_fieldMap, 2));
}

TEST_F(SquareFactoryTest, IsMine_WhenFalse)
{
	ASSERT_FALSE(_factory->IsMine(_fieldMap, 2));
}

TEST_F(SquareFactoryTest, IsMine_WhenIndexTooLarge)
{
	ASSERT_FALSE(_factory->IsMine(_fieldMap, _fieldMap.size()));
}

TEST_F(SquareFactoryTest, IsMine_WhenIndexTooSmall)
{
	ASSERT_FALSE(_factory->IsMine(_fieldMap, -1));
}
