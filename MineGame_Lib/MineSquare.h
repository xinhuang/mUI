#ifndef __MINESQUARE_H__
#define __MINESQUARE_H__

#include <ISquare.h>

class MGame;

class MineSquare : public ISquare
{
public:
	MineSquare(MGame* game);
	virtual SquareState::Enum get_State() const;

private:
	MGame* _game;
	SquareState::Enum _state;
};

#endif // __MINESQUARE_H__
