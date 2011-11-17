#ifndef __ISQUARE_H__
#define __ISQUARE_H__

namespace SquareState{
	enum Enum{
		Uncovered,
		Covered,
		Boomed,
		Flagged,
	};
};

class ISquare
{
public:
	virtual ~ISquare() {};
	virtual SquareState::Enum get_State() const = 0;
};

#endif // __ISQUARE_H__
