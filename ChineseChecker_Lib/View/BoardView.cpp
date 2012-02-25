#include "BoardView.h"

#include "SquareView.h"

#include <vector>
using namespace std;

struct BoardView::Data
{
    vector<SquareView*> squares;
};

BoardView::BoardView() 
    : _d(new Data())
{
    _d->squares.push_back(new SquareView());
    for (auto iter = _d->squares.begin(); iter != _d->squares.end(); ++iter)
        Controls.Add(**iter);
}

BoardView::~BoardView()
{
    for (auto iter = _d->squares.begin(); iter != _d->squares.end(); ++iter)
    {
        delete *iter;
    }
    delete _d;
}
