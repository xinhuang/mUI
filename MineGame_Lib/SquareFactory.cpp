#include "SquareFactory.h"

#include "NumberSquare.h"
#include "BlankSquare.h"
#include "MineSquare.h"
#include "MineField.h"

#include <mUI.h>
using mUI::System::Random;

int SquareFactory::GetArrayIndexFromRowColumn(int r, int c, int rowWidth)
{
	return r * rowWidth + c;
}

vector<ISquare*> SquareFactory::CreateSquares(MGame* game, MineField* mineField)
{
	vector<ISquare*> squares;
	vector<bool> mineFieldMap = GenerateMineFieldMap(*mineField);
	const Size& mineFieldSize = mineField->get_Size();

	for (int r = 0; r < mineFieldSize.Width; ++r)
	{
		for (int c = 0; c < mineFieldSize.Height; ++c)
		{
			int i = GetArrayIndexFromRowColumn(r, c, mineFieldSize.Width);
			if (mineFieldMap[i])
				squares.push_back(new MineSquare(game, mineField, r, c));
			else
				squares.push_back(new BlankSquare(game, mineField, r, c));
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
		int swapIndex = _random.Next(0, map.size());
		bool tmp = map[i];
		map[i] = map[swapIndex];
		map[swapIndex] = tmp;
	}

	return map;
}
