#include "BlankSquare.h"

#include "MineField.h"

BlankSquare::BlankSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
{
}

void BlankSquare::Uncover()
{
	get_MineField()->UncoverNeighborSquares(*this);
}
