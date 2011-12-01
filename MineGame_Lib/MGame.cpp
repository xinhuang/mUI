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
	return _mineField->get_Size();
}

void MGame::set_MineFieldWidth(int width)
{
	_mineField->set_Width(width);
}

void MGame::set_MineFieldHeight(int height)
{
	_mineField->set_Height(height);
}

void MGame::set_MineTotal(int mineTotal)
{
	_mineField->set_MineTotal(mineTotal);
}

int MGame::get_MineTotal() const
{
	return _mineField->get_MineTotal();
}
	
void MGame::NewGame()
{
	_mineField->Refresh();
}

void MGame::Uncover(int x, int y)
{
}

void MGame::Lose()
{

}

MineField* MGame::get_MineField()
{
	return _mineField;
}