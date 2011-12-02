#include "MineSquare.h"

#include "MGame.h"

MineSquare::MineSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
{
}

void MineSquare::Uncover()
{
	set_State(SquareState::Boomed);
	get_Game()->Lose();
}
