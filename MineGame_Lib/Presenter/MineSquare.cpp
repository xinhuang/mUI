#include "MineSquare.h"

#include "MGame.h"

MineSquare::MineSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
{
}

void MineSquare::Uncover()
{
	set_State(SquareState::Boomed);

	if (!get_Game()->IsLost())
		set_ViewState(SquareViewState::Boomed);
	else
		set_ViewState(SquareViewState::Mine);

	get_Game()->Lose();
}
