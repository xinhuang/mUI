#ifndef __NUMBERSQUARE_H__
#define __NUMBERSQUARE_H__

#include "AbstractSquare.h"

class MGame;
class MineField;

class NumberSquare : public AbstractSquare
{
	typedef AbstractSquare base;
public:
	NumberSquare(MGame* game, MineField* mineField, int x, int y);

	virtual void Uncover();

	int get_Number() const;

private:
	mutable int _number;
};

#endif // __NUMBERSQUARE_H__
