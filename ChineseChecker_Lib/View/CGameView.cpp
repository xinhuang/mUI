#include "CGameView.h"

#include "BoardView.h"

struct CGameView::Data
{
    BoardView* board;
};

CGameView::CGameView()
    : _d(new Data())
{
    InitializeComponents();

}

CGameView::~CGameView()
{
    delete _d->board;
    delete _d;
}

void CGameView::InitializeComponents()
{
    set_Size(Size(800, 600));
    set_Text(L"Chinese Checker");

    _d->board = new BoardView();
    _d->board->set_Size(get_Size());
    Controls.Add(*_d->board);
    _d->board->set_Anchor(AnchorStyles::All);
}
