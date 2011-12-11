#ifndef __SQUAREEVENTARGS_H__
#define __SQUAREEVENTARGS_H__

#include <mUI.h>
using namespace mUI::System;

class ISquareView;

class SquareEventArgs : public EventArgs
{
public:
    SquareEventArgs(ISquareView* squareView) 
        : _squareView(squareView)
    {
    }

	ISquareView* get_SquareView()
	{
		return _squareView;
	}
private:
	ISquareView* _squareView;
};

#endif // __SQUAREEVENTARGS_H__
