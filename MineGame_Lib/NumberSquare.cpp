#include "NumberSquare.h"

#include <mUI.h>

using namespace mUI::System;

NumberSquare::NumberSquare(MGame* game, MineField* mineField, int row, int column, int neighborMineTotal)
	: base(game, mineField, row, column)
	, _neighborMineTotal(neighborMineTotal)
{
	if (neighborMineTotal <= 0 || neighborMineTotal > 8)
		throw ArgumentException();
}

int NumberSquare::get_NeighborMineTotal() const
{
	return _neighborMineTotal;
}
