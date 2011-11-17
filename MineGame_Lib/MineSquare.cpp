#include "MineSquare.h"

MineSquare::MineSquare(MGame* game)
	: _state(SquareState::Covered), 
	_game(game)
{
}

SquareState::Enum MineSquare::get_State() const
{
	return _state;
}
