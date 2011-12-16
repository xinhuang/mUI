#include "BlankSquare.h"

#include "MineField.h"

BlankSquare::BlankSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
{
}

void BlankSquare::Uncover()
{
	set_State(SquareState::Uncovered);
	set_ViewState(SquareViewState::Blank);
	get_MineField()->UncoverAdjacent(this->get_Location());
}
