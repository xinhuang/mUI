#include "AbstractSquare.h"

AbstractSquare::AbstractSquare(MGame* game, MineField* mineField, int row, int column)
	: _state(SquareState::Covered)
{
}

SquareState::Enum AbstractSquare::get_State() const
{
	return _state;
}
