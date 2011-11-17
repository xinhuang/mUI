#include "MineField.h"
#include <mUI.h>

#include "MGame.h"

MineField::MineField(MGame* game)
	: _MGame(game)
{
}

const Size& MineField::get_Size() const
{
	return _MGame->get_MineFieldSize();
}

int MineField::get_MineTotal() const
{
	return _MGame->get_MineTotal();
}
