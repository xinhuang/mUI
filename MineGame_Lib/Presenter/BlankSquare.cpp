#include "BlankSquare.h"

#include "MineField.h"
#include "MGame.h"

BlankSquare::BlankSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
{
}

void BlankSquare::Uncover()
{
	if (get_Game()->IsLost())
		return;

	set_State(SquareState::Uncovered);
	set_ViewState(SquareViewState::Blank);
	get_MineField()->UncoverAdjacent(this->get_Location());
}
