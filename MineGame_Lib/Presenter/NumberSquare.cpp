#include "NumberSquare.h"

#include <mUI.h>
using namespace mUI::System;

#include "MineField.h"
#include "../View/View.h"

NumberSquare::NumberSquare(MGame* game, MineField* mineField, int x, int y)
	: base(game, mineField, Point(x, y))
	, _number(-1)
{
}

int NumberSquare::get_Number() const
{
	if (_number == -1)
		_number = get_MineField()->get_AdjacentMineTotal(this);
	return _number;
}

void NumberSquare::Uncover()
{
	if (get_State() == SquareState::Flagged)
		return;
	set_State(SquareState::Uncovered);
	UpdateView();
}

void NumberSquare::UpdateView()
{
	ISquareView* view = get_View();
	if (view == 0)
		return;

	view->set_Number(get_Number());
}
