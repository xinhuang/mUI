#include "BlankSquare.h"

#include "MineField.h"

BlankSquare::BlankSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
{
}

void BlankSquare::Uncover()
{
	get_MineField()->UncoverAdjacent(*this);
	set_State(SquareState::Uncovered);
	set_ViewState(SquareViewState::Blank);
}
