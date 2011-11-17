#include "NumberSquare.h"

NumberSquare::NumberSquare(MGame* game)
	: _state(SquareState::Covered), 
	_game(game)
{
}

SquareState::Enum NumberSquare::get_State() const
{
	return _state;
}
