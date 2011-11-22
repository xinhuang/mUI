#include "SquareFactory.h"

#include "NumberSquare.h"
#include "BlankSquare.h"
#include "MineSquare.h"

vector<ISquare*> SquareFactory::CreateSquares(MGame* game, MineField* mineField)
{
	vector<ISquare*> squares;
	squares.push_back(new MineSquare(game, mineField, 0, 0));
	return squares;
}
