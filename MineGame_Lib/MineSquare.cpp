#include "MineSquare.h"

#include "MGame.h"

MineSquare::MineSquare(MGame* game, MineField* mineField, int row, int column)
	: base(game, mineField, Point(row, column))
{
}

void MineSquare::Uncover()
{
	set_State(SquareState::Boomed);
	get_Game()->Lose();
}
