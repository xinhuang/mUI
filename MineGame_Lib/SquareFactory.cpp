#include "SquareFactory.h"

#include "NumberSquare.h"
#include "BlankSquare.h"
#include "MineSquare.h"
#include "MineField.h"

vector<ISquare*> SquareFactory::CreateSquares(MGame* game, MineField* mineField)
{
	vector<ISquare*> squares;
	int mineTotal = mineField->get_MineTotal();
	
	for (int r = 0; r < mineField->get_Size().Width; ++r)
		for (int c = 0; c < mineField->get_Size().Height; ++c)
		{
			if (mineTotal-- > 0)
				squares.push_back(new MineSquare(game, mineField, r, c));
			else
				squares.push_back(new BlankSquare(game, mineField, r, c));
		}

	return squares;
}
