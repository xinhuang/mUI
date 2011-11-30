#include <gtest\gtest.h>

#include <mUI.h>
using mUI::System::ArgumentException;

#define private public
#include <MGame.h>
#include <MineField.h>
#include <ISquare.h>
#undef private

#include "mocks/ISquareMock.h"

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

	int get_ArbitraryRowIndex() const
	{
		return static_cast<int>(_mineField->get_Size().Width * 0.8);
	}

	int get_ArbitraryColumnIndex() const
	{
		return static_cast<int>(_mineField->get_Size().Height * 0.7);
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

TEST_F(MineFieldTest, SquareAt_Typical)
{
	for (int r = 0; r < _mineField->get_Size().Width; ++r)
	{
		for (int c = 0; c < _mineField->get_Size().Height; ++c)
		{
			ISquare* square = _mineField->SquareAt(r, c);
			ASSERT_TRUE(NULL != square);
			ASSERT_EQ(r, square->get_Row());
			ASSERT_EQ(c, square->get_Column());
		}
	}
}

TEST_F(MineFieldTest, get_RowFromIndex_Typical)
{
	int r = get_ArbitraryRowIndex();
	int c = get_ArbitraryColumnIndex();
	int i = r * _mineField->get_Size().Width + c;

	ASSERT_EQ(r, _mineField->get_RowFromIndex(i));
}

TEST_F(MineFieldTest, get_RowFromIndex_WhenIndexTooLarge)
{
	int r = _mineField->get_Size().Width;
	int c = get_ArbitraryColumnIndex();
	int i = r * _mineField->get_Size().Width + c;

	try
	{
		_mineField->get_RowFromIndex(i);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_RowFromIndex_WhenIndexTooSmall)
{
	try
	{
		_mineField->get_RowFromIndex(-1);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_ColumnFromIndex_Typical)
{
	int r = get_ArbitraryRowIndex();
	int c = get_ArbitraryColumnIndex();
	int i = r * _mineField->get_Size().Width + c;

	ASSERT_EQ(c, _mineField->get_ColumnFromIndex(i));
}

TEST_F(MineFieldTest, get_ColumnFromIndex_WhenIndexTooLarge)
{
	int r = _mineField->get_Size().Width;
	int c = _mineField->get_Size().Height;
	int i = r * _mineField->get_Size().Width + c;

	try
	{
		_mineField->get_ColumnFromIndex(i);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_ColumnFromIndex_WhenIndexTooSmall)
{
	try
	{
		_mineField->get_ColumnFromIndex(-1);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_Index_Typical)
{
	int r = get_ArbitraryRowIndex();
	int c = get_ArbitraryColumnIndex();
	int i = r * _mineField->get_Size().Width + c;

	ASSERT_EQ(i, _mineField->get_Index(r, c));
}

TEST_F(MineFieldTest, get_Index_WhenColumnTooLarge)
{
	int r = get_ArbitraryRowIndex();
	int c = _mineField->get_Size().Height + 1;

	try
	{
		_mineField->get_Index(r, c);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_Index_WhenColumnTooSmall)
{
	int r = get_ArbitraryRowIndex();
	int c = -1;

	try
	{
		_mineField->get_Index(r, c);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_Index_WhenRowTooLarge)
{
	int r = _mineField->get_Size().Width + 1;
	int c = get_ArbitraryColumnIndex();

	try
	{
		_mineField->get_Index(r, c);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}

TEST_F(MineFieldTest, get_Index_WhenRowTooSmall)
{
	int r = -1;
	int c = get_ArbitraryColumnIndex();

	try
	{
		_mineField->get_Index(r, c);
		ASSERT_TRUE(FALSE);
	}
	catch (const ArgumentException&)
	{
	}
}
