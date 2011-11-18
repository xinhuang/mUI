#include "NumberSquare.h"

#include <mUI.h>

using namespace mUI::System;

NumberSquare::NumberSquare(MGame* game, MineField* mineField, int row, int column, int neighborMineTotal)
	: base(game, mineField, row, column)
{
	if (neighborMineTotal <= 0 || neighborMineTotal > 8)
		throw ArgumentException();
}
