#include "BlankSquare.h"

#include "MineField.h"

BlankSquare::BlankSquare(MGame* game, MineField* mineField, int row, int column)
	: base(game, mineField, Point(row, column))
{
}

void BlankSquare::Uncover()
{
	get_MineField()->UncoverNeighborSquares(*this);
}
