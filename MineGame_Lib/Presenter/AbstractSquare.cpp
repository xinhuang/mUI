#include "AbstractSquare.h"

#include "../View/View.h"

#include "MGame.h"

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
}

void AbstractSquare::ToggleFlag()
{
	if (get_Game()->IsLost())
		return;

	switch (get_State())
	{
	case SquareState::Covered:
		set_State(SquareState::Flagged);
		set_ViewState(SquareViewState::Flagged);
		break;

	case SquareState::Flagged:
		set_State(SquareState::Questioned);
		set_ViewState(SquareViewState::Questioned);
		break;

	case SquareState::Questioned:
		set_State(SquareState::Covered);
		set_ViewState(SquareViewState::Covered);
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

void AbstractSquare::set_ViewState( SquareViewState::Enum state )
{
	if (_view != 0)
	{
		_view->set_State(state);
	}
}
