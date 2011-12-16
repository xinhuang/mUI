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
	const vector<bool> fieldMap = GenerateMineFieldMap(mineField->get_Size(), 
														mineField->get_MineTotal());
	return CreateSquaresUsingFieldMap(game, mineField, fieldMap);
}

vector<ISquare*> SquareFactory::CreateSquaresUsingFieldMap( MGame* game, 
	MineField* mineField, const vector<bool>& fieldMap )
{
	const Size& size = mineField->get_Size();
	vector<ISquare*> squares(size.Width * size.Height, NULL);
	for (size_t i = 0; i < squares.size(); ++i)
	{
		if (fieldMap[i])
		{
			squares[i] = new MineSquare(game, mineField, 
				mineField->get_XFromIndex(i), mineField->get_YFromIndex(i));
		}
		else
		{
			if (HasAdjacentMine(fieldMap, mineField->get_Size(), i))
				squares[i] = new NumberSquare(game, mineField, 
				mineField->get_XFromIndex(i), mineField->get_YFromIndex(i));
			else
				squares[i] = new BlankSquare(game, mineField, 
				mineField->get_XFromIndex(i), mineField->get_YFromIndex(i));
		}
	}
	return squares;
}

vector<bool> SquareFactory::GenerateMineFieldMap( const Size& fieldSize, int mineTotal )
{
	vector<bool> map;
	
	for (int r = 0; r < fieldSize.Width; ++r)
	{
		for (int c = 0; c < fieldSize.Height; ++c)
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

bool SquareFactory::IsMineUp( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, i - fieldSize.Width);
}

bool SquareFactory::IsMineDown( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, i + fieldSize.Width);
}

bool SquareFactory::IsMineLeft( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, --i);
}

bool SquareFactory::IsMineRight( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, ++i);
}

bool SquareFactory::IsMineUpRight( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, i - fieldSize.Width + 1);
}

bool SquareFactory::IsMineDownRight( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, i + fieldSize.Width + 1);
}

bool SquareFactory::IsMineUpLeft( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, i - fieldSize.Width - 1);
}

bool SquareFactory::IsMineDownLeft( const vector<bool>& fieldMap, const Size& fieldSize, int i )
{
	return IsMine(fieldMap, i + fieldSize.Width - 1);
}

bool SquareFactory::IsMine( const vector<bool> &fieldMap, int i )
{
	if (i < 0)
		return false;
	if (static_cast<size_t>(i) < fieldMap.size())
		return fieldMap[i];
	return false;
}
