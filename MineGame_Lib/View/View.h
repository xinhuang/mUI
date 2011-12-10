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

class View
{
public:
    EventHandler<> NewGame;
    EventHandler<> FieldSizeChanged;
    EventHandler<> MineTotalChanged;
    EventHandler<SquareEventArgs*> UncoverSquare;
    EventHandler<SquareEventArgs*> ToggleFlagSquare;

	virtual void set_SquareState(const Point& location, SquareState::Enum state, IntPtr param) = 0;
	virtual void set_RemainingMineTotal(int remainingTotal) = 0;
};

#endif // __VIEW_H__
