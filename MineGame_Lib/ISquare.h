#ifndef __ISQUARE_H__
#define __ISQUARE_H__

namespace SquareState{
	enum Enum{
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
	virtual int get_Row() const = 0;
	virtual int get_Column() const = 0;

	virtual void Uncover() = 0;
	virtual void ToggleFlag() = 0;
};

#endif // __ISQUARE_H__
