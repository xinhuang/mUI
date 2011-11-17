#ifndef __NUMBERSQUARE_H__
#define __NUMBERSQUARE_H__

#include <ISquare.h>

class NumberSquare : public ISquare
{
public:
	NumberSquare();
	virtual SquareState::Enum get_State() const;

private:
	SquareState::Enum _state;
};

#endif // __NUMBERSQUARE_H__
