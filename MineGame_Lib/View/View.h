#ifndef __VIEW_H__
#define __VIEW_H__

class ISquare;

#include <mUI.h>
using namespace mUI;
using namespace mUI::System;
using namespace mUI::System::Drawing;

#include "SquareEventArgs.h"
#include "FieldSizeChangedEventArgs.h"
#include "MineTotalChangedEventArgs.h"
#include "ISquareView.h"

typedef EventHandler<SquareEventArgs*> SquareEventHandler;

class View
{
public:
    virtual ~View() {}

    EventHandler<> NewGame;
    EventHandler<FieldSizeChangedEventArgs*> FieldSizeChanged;
    EventHandler<MineTotalChangedEventArgs*> MineTotalChanged;
    SquareEventHandler SquareUncovered;
    SquareEventHandler SquareToggleFlag;

	virtual vector<ISquareView*> CreateSquares(const Size& size) = 0;
	virtual void set_RemainMineTotal(int remainingTotal) = 0;
	virtual void set_Lost(bool value) = 0;
};

#endif // __VIEW_H__
