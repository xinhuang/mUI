#include <gtest/gtest.h>

#include <mUI.h>
using mUI::System::ArgumentException;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/ISquare.h>

#include "mocks/SquareFactoryFake.h"
#include "mocks/ISquareMock.h"
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
		_mineField = _game->get_MineField();
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
		return static_cast<int>(_mineField->get_Size().Width * 0.8);
	}

	int get_ArbitraryX() const
	{
		return static_cast<int>(_mineField->get_Size().Height * 0.7);
	}

protected:
	static const int _arbitraryMineTotal = 20;
	static const int _arbitraryHeight = 20;
	static const int _arbitraryWidth = 20;
	MGame* _game;
	MineField* _mineField;
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
	ASSERT_EQ(_game->get_MineFieldSize(), _mineField->get_Size());
}

TEST_F(MineFieldTest, MineTotal_Typical)
{
	ASSERT_EQ(_game->get_MineTotal(), _mineField->get_MineTotal());
}

TEST_F(MineFieldTest, SquareAt_Typical)
{
	_mineField->Refresh();
	for (int r = 0; r < _mineField->get_Size().Width; ++r)
	{
		for (int c = 0; c < _mineField->get_Size().Height; ++c)
		{
			ISquare* square = _mineField->SquareAt(r, c);
			ASSERT_TRUE(NULL != square);
			ASSERT_EQ(r, square->get_X());
			ASSERT_EQ(c, square->get_Y());
		}
	}
}

TEST_F(MineFieldTest, get_YFromIndex_UpLeft)
{
	const Size& fieldSize = _mineField->get_Size();
	int maxIndex = _mineField->get_IndexMax();

	ASSERT_EQ(0, _mineField->get_YFromIndex(0));
	ASSERT_EQ(0, _mineField->get_YFromIndex(1));
	ASSERT_EQ(fieldSize.Height - 1, _mineField->get_YFromIndex(maxIndex - 1));
	ASSERT_EQ(fieldSize.Height - 1, _mineField->get_YFromIndex(maxIndex - fieldSize.Width));
}

TEST_F(MineFieldTest, get_YFromIndex_WhenIndexTooLarge)
{
	int r = _mineField->get_Size().Width;
	int c = get_ArbitraryX();
	int i = r * _mineField->get_Size().Width + c;

	try
	{
		_mineField->get_YFromIndex(i);
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
		_mineField->get_YFromIndex(-1);
		ASSERT_TRUE(false);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_XFromIndex_Typical)
{
	int r = get_ArbitraryY();
	int c = get_ArbitraryX();
	int i = r * _mineField->get_Size().Width + c;

	ASSERT_EQ(c, _mineField->get_XFromIndex(i));
}

TEST_F(MineFieldTest, get_XFromIndex_WhenIndexTooLarge)
{
	int r = _mineField->get_Size().Width;
	int c = _mineField->get_Size().Height;
	int i = r * _mineField->get_Size().Width + c;

	try
	{
		_mineField->get_XFromIndex(i);
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
		_mineField->get_XFromIndex(-1);
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
	int i = get_IndexFrom2D(_mineField->get_Size(), x, y);

	ASSERT_EQ(i, _mineField->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenXTooLarge)
{
	int y = get_ArbitraryY();
	int x = _mineField->get_Size().Height + 1;

	ASSERT_EQ(-1, _mineField->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenXTooSmall)
{
	int y = get_ArbitraryY();
	int x = -1;

	ASSERT_EQ(-1, _mineField->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenYTooLarge)
{
	int y = _mineField->get_Size().Width + 1;
	int x = get_ArbitraryX();

	ASSERT_EQ(-1, _mineField->get_Index(x, y));
}

TEST_F(MineFieldTest, get_Index_WhenYTooSmall)
{
	int y = -1;
	int x = get_ArbitraryX();

	ASSERT_EQ(-1, _mineField->get_Index(x, y));
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_When8Mines)
{
	SquareFactory* oldFactory = _mineField->get_SquareFactory();
	SquareFactoryFake newFactory(vector<bool>(9, true));
	_mineField->set_SquareFactory(&newFactory);
	_mineField->set_Size(Size(3, 3));
	_mineField->Refresh();

	ASSERT_EQ(8, _mineField->get_AdjacentMineTotal(Point(1, 1)));

	_mineField->set_SquareFactory(oldFactory);
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_WhenNoMine)
{
	SquareFactory* oldFactory = _mineField->get_SquareFactory();
	vector<bool> fieldMap(9, false);
	fieldMap[4] = true;
	SquareFactoryFake newFactory(fieldMap);
	_mineField->set_SquareFactory(&newFactory);
	_mineField->set_Size(Size(3, 3));
	_mineField->Refresh();

	ASSERT_EQ(0, _mineField->get_AdjacentMineTotal(Point(1, 1)));

	_mineField->set_SquareFactory(oldFactory);
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_WhenMinesAtFourCorner)
{
	SquareFactory* oldFactory = _mineField->get_SquareFactory();
	vector<bool> fieldMap(9, false);
	fieldMap[4] = true;
	fieldMap[0] = true;
	fieldMap[2] = true;
	fieldMap[6] = true;
	fieldMap[8] = true;
	SquareFactoryFake newFactory(fieldMap);
	_mineField->set_SquareFactory(&newFactory);
	_mineField->set_Size(Size(3, 3));
	_mineField->Refresh();

	ASSERT_EQ(4, _mineField->get_AdjacentMineTotal(Point(1, 1)));

	_mineField->set_SquareFactory(oldFactory);
}

TEST_F(MineFieldTest, get_AdjacentMineTotal_WhenSquareIsAtBoundary)
{
	SquareFactory* oldFactory = _mineField->get_SquareFactory();
	vector<bool> fieldMap(9, true);
	SquareFactoryFake newFactory(fieldMap);
	_mineField->set_SquareFactory(&newFactory);
	_mineField->set_Size(Size(3, 3));
	_mineField->Refresh();

	ASSERT_EQ(3, _mineField->get_AdjacentMineTotal(Point(2, 2)));

	_mineField->set_SquareFactory(oldFactory);
}
