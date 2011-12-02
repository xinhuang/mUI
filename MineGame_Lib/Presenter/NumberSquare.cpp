#include "NumberSquare.h"

#include <mUI.h>
using namespace mUI::System;

#include "MineField.h"

NumberSquare::NumberSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
	, _number(-1)
{
}

int NumberSquare::get_Number() const
{
	if (_number == -1)
		_number = get_MineField()->get_NeighborMineTotal(this);
	return _number;
}

void NumberSquare::Uncover()
{
	if (get_State() == SquareState::Flagged)
		return;
	set_State(SquareState::Uncovered);
}
