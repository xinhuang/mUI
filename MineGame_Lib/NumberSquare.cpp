#include "NumberSquare.h"

#include <mUI.h>
using namespace mUI::System;

#include "MineField.h"

NumberSquare::NumberSquare(MGame* game, MineField* mineField, int row, int column)
	: base(game, mineField, Point(row, column))
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
