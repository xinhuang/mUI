#ifndef __MINESQUARE_H__
#define __MINESQUARE_H__

#include <AbstractSquare.h>

class MGame;

class MineSquare : public AbstractSquare
{
	typedef AbstractSquare base;
public:
	MineSquare(MGame* game, MineField* mineField, int x, int y);

	virtual void Uncover();
	virtual bool HasMine() const { return true; }

private:
	MGame* _game;
};

#endif // __MINESQUARE_H__
