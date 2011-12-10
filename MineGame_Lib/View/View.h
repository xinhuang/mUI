#ifndef __VIEW_H__
#define __VIEW_H__

#include "../Presenter/ISquare.h"

#include <mUI.h>
using namespace mUI;
using namespace mUI::System;
using namespace mUI::System::Drawing;

class SquareEventArgs : public EventArgs
{
public:
    SquareEventArgs(const Point& location) 
        : _location(location)
    {
    }

    const Point& get_Location() const { return _location; }

private:
    const Point _location;
};

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

class View
{
public:
    EventHandler<> NewGame;
    EventHandler<FieldSizeChangedEventArgs*> FieldSizeChanged;
    EventHandler<MineTotalChangedEventArgs*> MineTotalChanged;
    EventHandler<SquareEventArgs*> UncoverSquare;
    EventHandler<SquareEventArgs*> ToggleFlagSquare;

	virtual void set_SquareState(const Point& location, SquareState::Enum state, IntPtr param) = 0;
	virtual void set_RemainingMineTotal(int remainingTotal) = 0;
};

#endif // __VIEW_H__
