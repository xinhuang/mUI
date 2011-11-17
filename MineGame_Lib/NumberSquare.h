#ifndef __NUMBERSQUARE_H__
#define __NUMBERSQUARE_H__

#include <ISquare.h>

class MGame;

class NumberSquare : public ISquare
{
public:
	NumberSquare(MGame* game);
	virtual SquareState::Enum get_State() const;

private:
	MGame* _game;
	SquareState::Enum _state;
};

#endif // __NUMBERSQUARE_H__
