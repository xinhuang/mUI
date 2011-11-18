#ifndef __MINESQUARE_H__
#define __MINESQUARE_H__

#include <AbstractSquare.h>

class MGame;

class MineSquare : public AbstractSquare
{
	typedef AbstractSquare base;
public:
	MineSquare(MGame* game, MineField* mineField, int row, int column);

	virtual void Uncover();

private:
	MGame* _game;
};

#endif // __MINESQUARE_H__
