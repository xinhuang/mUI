#include "AbstractSquare.h"

AbstractSquare::AbstractSquare(MGame* game, MineField* mineField, int row, int column)
	: _state(SquareState::Covered)
	, _row(row)
	, _column(column)
{
}

SquareState::Enum AbstractSquare::get_State() const
{
	return _state;
}
