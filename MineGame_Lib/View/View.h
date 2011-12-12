#ifndef __VIEW_H__
#define __VIEW_H__

#include "../Presenter/ISquare.h"
#include "SquareEventArgs.h"

#include <mUI.h>
using namespace mUI;
using namespace mUI::System;
using namespace mUI::System::Drawing;


class FieldSizeChangedEventArgs : public EventArgs
{
public:
    FieldSizeChangedEventArgs(const Size& size)
        : _size(size)
    {}

    const Size& get_Size() const { return _size; }

private:
    const Size _size;
};

class MineTotalChangedEventArgs : public EventArgs
{
public:
    MineTotalChangedEventArgs(int mineTotal)
        : _mineTotal(mineTotal)
    {}

    int get_MineTotal() const { return _mineTotal; }

private:
    const int _mineTotal;
};

class ISquareView
{
public:
	virtual ~ISquareView() {}
	virtual void set_State(SquareState::Enum state) = 0;
	virtual const Point& get_Location() const = 0;
};

typedef EventHandler<SquareEventArgs*> SquareEventHandler;
class View
{
public:
    virtual ~View() {}

    EventHandler<> NewGame;
    EventHandler<FieldSizeChangedEventArgs*> FieldSizeChanged;
    EventHandler<MineTotalChangedEventArgs*> MineTotalChanged;
    SquareEventHandler SquareUncovered;
    SquareEventHandler ToggleFlagSquare;

	virtual vector<ISquareView*> CreateSquares(const Size& size) = 0;
	virtual void set_RemainingMineTotal(int remainingTotal) = 0;
};

#endif // __VIEW_H__
