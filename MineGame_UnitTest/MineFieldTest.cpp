#include <gtest/gtest.h>

#include <mUI.h>
using mUI::System::ArgumentException;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/ISquare.h>

#include "mocks/SquareFactoryMock.h"
#include "mocks/ViewMock.h"

class MineFieldTest : public testing::Test
{
public:
	void SetUp()
	{
        _view = new ViewMock();
		_game = new MGame(_view);
		_game->set_MineFieldHeight(_arbitraryHeight);
		_game->set_MineFieldWidth(_arbitraryWidth);
		_game->set_MineTotal(_arbitraryMineTotal);
		_sut = _game->get_MineField();
	}

	void TearDown()
	{
		delete _game;
        delete _view;
	}

	int get_IndexFrom2D(const Size& size, int x, int y)
	{
		return y * size.Width + x;
	}

	int get_ArbitraryY() const
	{
		return static_cast<int>(_sut->get_Size().Height * 0.8);
	}

	int get_ArbitraryX() const
	{
		return static_cast<int>(_sut->get_Size().Width * 0.7);
    }

    void VerifyFieldMapSize(const MineField::FieldMap& fieldMap, const Size& expectedSize) 
    {
        ASSERT_EQ(expectedSize.Width, fieldMap.size());
        for (size_t i = 0; i < fieldMap.size(); ++i)
        {
            ASSERT_EQ(expectedSize.Height, fieldMap[i].size());
        }
    }

    void VerifyFieldMapMineTotal(const MineField::FieldMap& fieldMap, int expectedMineTotal) 
    {
        int mineTotal = 0;
        for (size_t x = 0; x < fieldMap.size(); ++x)
        {
            for (size_t y = 0; y < fieldMap[x].size(); ++y)
            {
                mineTotal += fieldMap[x][y] ? 1 : 0;
            }
        }
        ASSERT_EQ(expectedMineTotal, mineTotal);
    }

protected:
	static const int _arbitraryMineTotal = 20;
	static const int _arbitraryHeight = 70;
	static const int _arbitraryWidth = 20;
	MGame* _game;
	MineField* _sut;
    ViewMock* _view;
};

TEST_F(MineFieldTest, Constructor_Typical)
{
	MineField* mineField = new MineField(_game);

	ASSERT_TRUE(NULL != mineField);
	delete mineField;
}

TEST_F(MineFieldTest, Size_Typical)
{
	ASSERT_EQ(_game->get_MineFieldSize(), _sut->get_Size());
}

TEST_F(MineFieldTest, MineTotal_Typical)
{
	ASSERT_EQ(_game->get_MineTotal(), _sut->get_MineTotal());
}

TEST_F(MineFieldTest, SquareAt_Typical)
{
	_sut->Refresh();
	for (int y = 0; y < _sut->get_Size().Height; ++y)
	{
		for (int x = 0; x < _sut->get_Size().Width; ++x)
		{
			ISquare* square = _sut->SquareAt(x, y);
			ASSERT_TRUE(NULL != square);
			ASSERT_EQ(x, square->get_X());
			ASSERT_EQ(y, square->get_Y());
		}
	}
}

TEST_F(MineFieldTest, get_YFromIndex_UpLeft)
{
	const Size& fieldSize = _sut->get_Size();
	int maxIndex = _sut->get_IndexMax();

	ASSERT_EQ(0, _sut->get_YFromIndex(0));
	ASSERT_EQ(0, _sut->get_YFromIndex(1));
	ASSERT_EQ(fieldSize.Height - 1, _sut->get_YFromIndex(maxIndex - 1));
	ASSERT_EQ(fieldSize.Height - 1, _sut->get_YFromIndex(maxIndex - fieldSize.Width));
}

TEST_F(MineFieldTest, get_YFromIndex_WhenIndexTooLarge)
{
	int y = _sut->get_Size().Height;
	int x = get_ArbitraryX();
	int i = y * _sut->get_Size().Width + x;

	try
	{
		_sut->get_YFromIndex(i);
		ASSERT_TRUE(false);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_YFromIndex_WhenIndexTooSmall)
{
	try
	{
		_sut->get_YFromIndex(-1);
		ASSERT_TRUE(false);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_XFromIndex_Typical)
{
	int y = get_ArbitraryY();
	int x = get_ArbitraryX();
	int i = y * _sut->get_Size().Width + x;

	ASSERT_EQ(x, _sut->get_XFromIndex(i));
}

TEST_F(MineFieldTest, get_XFromIndex_WhenIndexTooLarge)
{
	int y = _sut->get_Size().Height;
	int x = _sut->get_Size().Width;
	int i = y * _sut->get_Size().Width + x;

	try
	{
		_sut->get_XFromIndex(i);
		ASSERT_TRUE(false);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_XFromIndex_WhenIndexTooSmall)
{
	try
	{
		_sut->get_XFromIndex(-1);
		ASSERT_TRUE(false);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_Index_Typical)
{
	int y = get_ArbitraryY();
	int x = get_ArbitraryX();
	int i = get_IndexFrom2D(_sut->get_Size(), x, y);

	ASSERT_EQ(i, _sut->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenXTooLarge)
{
	int y = get_ArbitraryY();
	int x = _sut->get_Size().Width + 1;

	ASSERT_EQ(-1, _sut->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenXTooSmall)
{
	int y = get_ArbitraryY();
	int x = -1;

	ASSERT_EQ(-1, _sut->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenYTooLarge)
{
	int y = _sut->get_Size().Height + 1;
	int x = get_ArbitraryX();

	ASSERT_EQ(-1, _sut->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenYTooSmall)
{
	int y = -1;
	int x = get_ArbitraryX();

	ASSERT_EQ(-1, _sut->get_Index(x, y));
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_When8Mines)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	SquareFactoryFake newFactory(vector<bool>(9, true));
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(3, 3));
	_sut->Refresh();

	ASSERT_EQ(8, _sut->get_AdjacentMineTotal(Point(1, 1)));

	_sut->set_SquareFactory(oldFactory);
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_WhenNoMine)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	vector<bool> fieldMap(9, false);
	fieldMap[4] = true;
	SquareFactoryFake newFactory(fieldMap);
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(3, 3));
	_sut->Refresh();

	ASSERT_EQ(0, _sut->get_AdjacentMineTotal(Point(1, 1)));

	_sut->set_SquareFactory(oldFactory);
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_WhenMinesAtFourCorner)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	vector<bool> fieldMap(9, false);
	fieldMap[4] = true;
	fieldMap[0] = true;
	fieldMap[2] = true;
	fieldMap[6] = true;
	fieldMap[8] = true;
	SquareFactoryFake newFactory(fieldMap);
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(3, 3));
	_sut->Refresh();

	ASSERT_EQ(4, _sut->get_AdjacentMineTotal(Point(1, 1)));

	_sut->set_SquareFactory(oldFactory);
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_WhenSquareIsAtBoundary)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	vector<bool> fieldMap(9, true);
	SquareFactoryFake newFactory(fieldMap);
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(3, 3));
	_sut->Refresh();
	_sut->set_SquareFactory(oldFactory);

	ASSERT_EQ(3, _sut->get_AdjacentMineTotal(Point(2, 2)));
}

TEST_F(MineFieldTest, UncoverAdjacent_Typical)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	vector<bool> fieldMap(9, false);
	SquareFactoryFake newFactory(fieldMap);
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(3, 3));
	_sut->Refresh();
	_sut->set_SquareFactory(oldFactory);

	_sut->UncoverAdjacent(Point(1, 1));

	for (int i = 0; i < 9; ++i)
	{
		ASSERT_EQ(SquareState::Uncovered, _sut->SquareAt(i)->get_State());
	}
}

TEST_F(MineFieldTest, UncoverAdjacent_WhenAtCorner)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	vector<bool> fieldMap(6, false);
	SquareFactoryFake newFactory(fieldMap);
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(2, 3));
	_sut->Refresh();
	_sut->set_SquareFactory(oldFactory);

	_sut->UncoverAdjacent(Point(1, 1));

	for (int i = 0; i < 6; ++i)
	{
		ASSERT_EQ(SquareState::Uncovered, _sut->SquareAt(i)->get_State());
	}
}

TEST_F(MineFieldTest, UncoverAdjacent_WhenOneMine)
{
	SquareFactory* oldFactory = _sut->get_SquareFactory();
	vector<bool> fieldMap(9, false);
	fieldMap[0] = true;
	SquareFactoryFake newFactory(fieldMap);
	_sut->set_SquareFactory(&newFactory);
	_sut->set_Size(Size(3, 3));
	_sut->Refresh();
	_sut->set_SquareFactory(oldFactory);

	_sut->UncoverAdjacent(Point(2, 2));

	ASSERT_EQ(SquareState::Covered, _sut->SquareAt(0)->get_State());
	for (int i = 1; i < 9; ++i)
	{
		ASSERT_EQ(SquareState::Uncovered, _sut->SquareAt(i)->get_State());
	}
}

TEST_F(MineFieldTest, GenerateFieldMap_When1x1Mine0)
{
    MineField::FieldMap fieldMap = 
        _sut->GenerateFieldMap(Size(1, 1), 0);

    ASSERT_EQ(1, fieldMap.size());
    ASSERT_EQ(1, fieldMap[0].size());
    ASSERT_FALSE(fieldMap[0][0]);
}

TEST_F(MineFieldTest, GenerateFieldMap_When1x1Mine1)
{
    MineField::FieldMap fieldMap = 
        _sut->GenerateFieldMap(Size(1, 1), 1);

    ASSERT_EQ(1, fieldMap.size());
    ASSERT_EQ(1, fieldMap[0].size());
    ASSERT_TRUE(fieldMap[0][0]);
}

TEST_F(MineFieldTest, GenerateFieldMap_When2x1Mine0)
{
    MineField::FieldMap fieldMap = 
        _sut->GenerateFieldMap(Size(2, 1), 0);

    ASSERT_EQ(2, fieldMap.size());
    ASSERT_EQ(1, fieldMap[0].size());
    ASSERT_EQ(1, fieldMap[1].size());
    ASSERT_FALSE(fieldMap[0][0]);
    ASSERT_FALSE(fieldMap[1][0]);
}

TEST_F(MineFieldTest, GenerateFieldMap_When2x1Mine1)
{
    MineField::FieldMap fieldMap = 
        _sut->GenerateFieldMap(Size(2, 1), 1);

    ASSERT_EQ(2, fieldMap.size());
    ASSERT_EQ(1, fieldMap[0].size());
    ASSERT_EQ(1, fieldMap[1].size());
    ASSERT_TRUE(fieldMap[0][0] ^ fieldMap[1][0]);
}

TEST_F(MineFieldTest, GenerateFieldMap_When2x1Mine2)
{
    MineField::FieldMap fieldMap = 
        _sut->GenerateFieldMap(Size(2, 1), 2);

    ASSERT_EQ(2, fieldMap.size());
    ASSERT_EQ(1, fieldMap[0].size());
    ASSERT_EQ(1, fieldMap[1].size());
    ASSERT_TRUE(fieldMap[0][0]);
    ASSERT_TRUE(fieldMap[1][0]);
}

TEST_F(MineFieldTest, GenerateFieldMap_When10x10Mine37)
{
    int arbitraryMineTotal = 37;
    Size arbitrarySize(10, 10);

    MineField::FieldMap fieldMap = 
        _sut->GenerateFieldMap(arbitrarySize, arbitraryMineTotal);

    VerifyFieldMapSize(fieldMap, arbitrarySize);
    VerifyFieldMapMineTotal(fieldMap, arbitraryMineTotal);
}

TEST_F(MineFieldTest, GenerateFieldMap_WhenManyTimesCheckRandomness)
{
    int arbitraryMineTotal = 37;
    Size arbitrarySize(10, 10);

    MineField::FieldMap firstMap = 
        _sut->GenerateFieldMap(arbitrarySize, arbitraryMineTotal);

    for (int i = 0; i < 10; ++i)
    {
        MineField::FieldMap otherMap = 
            _sut->GenerateFieldMap(arbitrarySize, arbitraryMineTotal);
        if (otherMap != firstMap)
            return;
    }
    ASSERT_FALSE(true);
}
