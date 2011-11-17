#include "MGame.h"
#include "MineField.h"

#include <mUI.h>

MGame::MGame()
	: _MineField(NULL)
{
}

MGame::~MGame()
{
	delete _MineField;
}

const Size& MGame::get_MineFieldSize() const
{
	return _MineFieldSize;
}

void MGame::set_MineFieldWidth(int width)
{
	_MineFieldSize.Width = width;
}

void MGame::set_MineFieldHeight(int height)
{
	_MineFieldSize.Height = height;
}

void MGame::set_MineTotal(int mineTotal)
{
	_MineTotal = mineTotal;
}

int MGame::get_MineTotal() const
{
	return _MineTotal;
}
	
void MGame::NewGame()
{
	delete _MineField;
	_MineField = new MineField(this);
}

void MGame::Uncover(int rowIndex, int columnIndex)
{
}
