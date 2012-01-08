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
#include "mocks/ViewMock.h"

class SquareFactoryTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = new SquareFactory();
		_fieldMap.resize(9, false);
		_fieldSize = Size(3, 3);
		_view = new ViewMock();
		_game = new MGame(_view);
        _mineField = _game->get_MineField();
	}

	virtual void TearDown()
	{
		delete _sut;
		_sut = null;
		for(size_t i = 0; i < _squares.size(); ++i)
			delete _squares[i];
		_squares.clear();
		delete _game;
		_game = null;
		delete _view;
    }

    MineField::FieldMap CreateFieldMap(int value, const Size& size) 
    {
        MineField::FieldMap fieldMap(size.Height, vector<bool>(size.Width));
        for (int y = 0; y < size.Height; ++y)
        {
            for (int x = 0; x < size.Width; ++x)
            {
                int i = y * size.Width + x;
                fieldMap[y][x] = (value & (1 << i)) != 0;
            }
        }
        return fieldMap;
    }

    bool HasElementTrue( const vector<bool>& fieldMap ) 
    {
        for (size_t i = 0; i < fieldMap.size(); ++i)
        {
            if (fieldMap[i])
                return true;
        }
        return false;
    }

protected:
	MGame* _game;
	SquareFactory* _sut;
	vector<ISquare*> _squares;
	vector<bool> _fieldMap;
	static const int _middleSquareIndex = 4;
	Size _fieldSize;
	View* _view;
    MineField* _mineField;
};

TEST_F(SquareFactoryTest, Constructor_Typical)
{
	ASSERT_TRUE(null != _sut);
}

TEST_F(SquareFactoryTest, CreateSquares_When1x1Mine0)
{
    MineField::FieldMap fieldMap(1, vector<bool>(1));

    vector<ISquare*> squares = _sut->CreateSquares(_game, _mineField, fieldMap);

    ASSERT_EQ(1, squares.size());
    ASSERT_EQ(typeid(BlankSquare), typeid(*squares[0]));
}

TEST_F(SquareFactoryTest, CreateSquares_When1x1Mine1)
{
    MineField::FieldMap fieldMap(1, vector<bool>(1, true));

    vector<ISquare*> squares = _sut->CreateSquares(_game, _mineField, fieldMap);

    ASSERT_EQ(1, squares.size());
    ASSERT_EQ(typeid(MineSquare), typeid(*squares[0]));
}

TEST_F(SquareFactoryTest, CreateSquares_When1x2Mine0)
{
    MineField::FieldMap fieldMap(1, vector<bool>(2));

    vector<ISquare*> squares = _sut->CreateSquares(_game, _mineField, fieldMap);

    ASSERT_EQ(2, squares.size());
    ASSERT_EQ(typeid(BlankSquare), typeid(*squares[0]));
    ASSERT_EQ(typeid(BlankSquare), typeid(*squares[1]));
}

TEST_F(SquareFactoryTest, CreateSquares_When1x2Mine1)
{
    MineField::FieldMap fieldMap(1, vector<bool>(2));
    fieldMap[0][1] = true;

    vector<ISquare*> squares = _sut->CreateSquares(_game, _mineField, fieldMap);

    ASSERT_EQ(2, squares.size());
    ASSERT_EQ(typeid(NumberSquare), typeid(*squares[0]));
    ASSERT_EQ(typeid(MineSquare), typeid(*squares[1]));
}

TEST_F(SquareFactoryTest, CreateSquares_When1x3Mine1)
{
    MineField::FieldMap fieldMap(1, vector<bool>(3));
    fieldMap[0][0] = true;

    vector<ISquare*> squares = _sut->CreateSquares(_game, _mineField, fieldMap);

    ASSERT_EQ(3, squares.size());
    ASSERT_EQ(typeid(MineSquare), typeid(*squares[0]));
    ASSERT_EQ(typeid(NumberSquare), typeid(*squares[1]));
    ASSERT_EQ(typeid(BlankSquare), typeid(*squares[2]));
}

TEST_F(SquareFactoryTest, HasAdjacentMine_BruteForce)
{
    for (int value = 0; value < 0x200; ++value)
    {
        MineField::FieldMap fieldMap = CreateFieldMap(value, Size(3, 3));
        bool expect = (value & 0x1EF) != 0;

        ASSERT_EQ(expect, _sut->HasAdjacentMine(fieldMap, 1, 1));
    }
}
