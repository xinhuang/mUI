#include "NumberSquare.h"

NumberSquare::NumberSquare()
	: _state(SquareState::Covered)
{
}

SquareState::Enum NumberSquare::get_State() const
{
	return _state;
}
