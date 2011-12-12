#include "AbstractSquare.h"
#include "../View/View.h"

AbstractSquare::AbstractSquare(MGame* game, MineField* mineField, const Point& location)
	: _state(SquareState::Covered)
	, _game(game)
	, _mineField(mineField)
	, _location(location)
	, _view(0)
{
}

SquareState::Enum AbstractSquare::get_State() const
{
	return _state;
}

void AbstractSquare::set_State(SquareState::Enum state)
{
	_state = state;
	if (_view != 0)
		_view->set_State(_state);
}

void AbstractSquare::ToggleFlag()
{
	switch (get_State())
	{
	case SquareState::Covered:
		set_State(SquareState::Flagged);
		break;

	case SquareState::Flagged:
		set_State(SquareState::QuestionMark);
		break;

	case SquareState::QuestionMark:
		set_State(SquareState::Uncovered);
		break;

	default:
		break;
	}
}

MGame* AbstractSquare::get_Game()
{
	return _game;
}

MineField* AbstractSquare::get_MineField()
{
	return _mineField;
}

const MGame* AbstractSquare::get_Game() const
{
	return _game;
}

const MineField* AbstractSquare::get_MineField() const
{
	return _mineField;
}

void AbstractSquare::Bind( ISquareView* view )
{
	_view = view;
}

ISquareView* AbstractSquare::get_View()
{
	return _view;
}
