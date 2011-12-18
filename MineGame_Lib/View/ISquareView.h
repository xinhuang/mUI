#ifndef __ISQUAREVIEW_H__
#define __ISQUAREVIEW_H__

#include "SquareViewState.h"

#include <mUI.h>
using mUI::System::Drawing::Point;

class ISquareView
{
public:
	virtual ~ISquareView() {}
	virtual void set_State(SquareViewState::Enum state) = 0;
	virtual const Point& get_Coordinates() const = 0;
};

#endif // __ISQUAREVIEW_H__
