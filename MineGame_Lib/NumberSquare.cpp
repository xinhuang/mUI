#include "NumberSquare.h"

#include <mUI.h>

using namespace mUI::System;

NumberSquare::NumberSquare(MGame* game, int neighborMineTotal)
	: _state(SquareState::Covered), 
	_game(game)
{
	if (neighborMineTotal <= 0 || neighborMineTotal > 8)
		throw ArgumentException();
}

SquareState::Enum NumberSquare::get_State() const
{
	return _state;
}
