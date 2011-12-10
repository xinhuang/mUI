#include "MGame.h"
#include "MineField.h"

#include <mUI.h>
#include "../View/View.h"

MGame::MGame(View* view)
	: _mineField(NULL)
    , _view(view)
{
	_mineField = new MineField(this);
    view->FieldSizeChanged += EventHandler<FieldSizeChangedEventArgs*>(this, &MGame::OnFieldSizeChanged);
    view->MineTotalChanged += EventHandler<MineTotalChangedEventArgs*>(this, &MGame::OnMineTotalChanged);
    view->NewGame += EventHandler<>(this, &MGame::OnNewGame);
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
    _view->CreateSquares(_mineField->get_Size());
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

void MGame::OnNewGame( void* sender, EventArgs* e )
{
    NewGame();
}

void MGame::OnFieldSizeChanged( void* sender, FieldSizeChangedEventArgs* e )
{
    set_MineFieldHeight(e->get_Size().Height);
    set_MineFieldWidth(e->get_Size().Width);
}

void MGame::OnMineTotalChanged( void* sender, MineTotalChangedEventArgs* e )
{
    set_MineTotal(e->get_MineTotal());
}
