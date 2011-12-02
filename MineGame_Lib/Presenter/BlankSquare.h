#ifndef __BLANKSQUARE_H__
#define __BLANKSQUARE_H__

#include "AbstractSquare.h"

class MGame;

class BlankSquare : public AbstractSquare
{
	typedef AbstractSquare base;
public:
	BlankSquare(MGame* game, MineField* mineField, int x, int y);

	virtual void Uncover();
};

#endif // __BLANKSQUARE_H__
