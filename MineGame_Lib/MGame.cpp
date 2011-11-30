#include "MGame.h"
#include "MineField.h"

#include <mUI.h>

MGame::MGame()
	: _mineField(NULL)
{
	_mineField = new MineField(this);
}

MGame::~MGame()
{
	delete _mineField;
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
	_mineField->Refresh();
}

void MGame::Uncover(int rowIndex, int columnIndex)
{
}

void MGame::Lose()
{

}
