#ifndef __ISQUARE_H__
#define __ISQUARE_H__

#include <mUI.h>
using mUI::System::Drawing::Point;

namespace SquareState{
	enum Enum
	{
		Uncovered,
		Covered,
		Boomed,
		Flagged,
		QuestionMark,
	};
};

class ISquare
{
public:
	virtual ~ISquare() {};

	virtual SquareState::Enum get_State() const = 0;
	virtual int get_X() const = 0;
	virtual int get_Y() const = 0;

	virtual void Uncover() = 0;
	virtual void ToggleFlag() = 0;
	virtual bool HasMine() const = 0;

	virtual const Point& get_Location() const = 0;
};

#endif // __ISQUARE_H__