#include "BlankSquare.h"

BlankSquare::BlankSquare(MGame* game)
	: _state(SquareState::Covered), 
	_game(game)
{
}

SquareState::Enum BlankSquare::get_State() const
{
	return _state;
}
