#include "SquareFactory.h"

#include "NumberSquare.h"
#include "BlankSquare.h"
#include "MineSquare.h"
#include "MineField.h"

#include <algorithm>
using std::swap;

#include <mUI.h>
using mUI::System::Random;
using mUI::System::Drawing::Point;

vector<ISquare*> SquareFactory::CreateSquares(MGame* game, MineField* mineField)
{
	const Size& size = mineField->get_Size();
	vector<ISquare*> squares(size.Width * size.Height, NULL);

	const vector<bool> fieldMap = GenerateMineFieldMap(*mineField);

	for (size_t i = 0; i < squares.size(); ++i)
	{
		if (fieldMap[i])
		{
			squares[i] = new MineSquare(game, mineField, 
				mineField->get_RowFromIndex(i), mineField->get_ColumnFromIndex(i));
		}
		else
		{
			if (HasAdjacentMine(fieldMap, mineField->get_Size(), i))
				squares[i] = new NumberSquare(game, mineField, 
					mineField->get_RowFromIndex(i), mineField->get_ColumnFromIndex(i));
			else
				squares[i] = new BlankSquare(game, mineField, 
					mineField->get_RowFromIndex(i), mineField->get_ColumnFromIndex(i));
		}
	}

	return squares;
}

vector<bool> SquareFactory::GenerateMineFieldMap(const MineField& mineField)
{
	vector<bool> map;
	int mineTotal = mineField.get_MineTotal();
	
	for (int r = 0; r < mineField.get_Size().Width; ++r)
	{
		for (int c = 0; c < mineField.get_Size().Height; ++c)
		{
			if (mineTotal-- > 0)
				map.push_back(true);
			else
				map.push_back(false);
		}
	}

	for (size_t i = 0; i < map.size(); ++i)
	{
		int swapIndex = _random.Next(map.size());
		bool tmp = map[i];
		map[i] = map[swapIndex];
		map[swapIndex] = tmp;
	}

	return map;
}

bool SquareFactory::HasAdjacentMine( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return IsMineUp(fieldMap, fieldSize, i) || IsMineDown(fieldMap, fieldSize, i) 
		|| IsMineLeft(fieldMap, fieldSize, i) || IsMineRight(fieldMap, fieldSize, i)
		|| IsMineUpRight(fieldMap, fieldSize, i) || IsMineDownRight(fieldMap, fieldSize, i) 
		|| IsMineUpLeft(fieldMap, fieldSize, i) || IsMineDownLeft(fieldMap, fieldSize, i);
}

bool SquareFactory::IsMineUp( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	int r = MineField::get_RowFromIndex(fieldSize, i);
	int c = MineField::get_ColumnFromIndex(fieldSize, i);
	if (r == 0)
	{
		return false;
	}
	else
	{
		int i = MineField::get_Index(fieldSize, r - 1, c);
		return fieldMap[i];
	}
}

bool SquareFactory::IsMineDown( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}

bool SquareFactory::IsMineLeft( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}

bool SquareFactory::IsMineRight( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}

bool SquareFactory::IsMineUpRight( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}

bool SquareFactory::IsMineDownRight( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}

bool SquareFactory::IsMineUpLeft( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}

bool SquareFactory::IsMineDownLeft( const vector<bool>& fieldMap, const Size& fieldSize, size_t i )
{
	return false;
}