#ifndef __NUMBERSQUARE_H__
#define __NUMBERSQUARE_H__

#include "AbstractSquare.h"

class MGame;
class MineField;

class NumberSquare : public AbstractSquare
{
	typedef AbstractSquare base;
public:
	NumberSquare(MGame* game, MineField* mineField, int row, int column, int neighborMineTotal);

	virtual void Uncover();

	int get_NeighborMineTotal() const;

private:
	int _neighborMineTotal;
};

#endif // __NUMBERSQUARE_H__
