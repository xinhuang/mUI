#ifndef __BLANKSQUARE_H__
#define __BLANKSQUARE_H__

#include <ISquare.h>

class MGame;

class BlankSquare : public ISquare
{
public:
	BlankSquare(MGame* game);
	virtual SquareState::Enum get_State() const;

private:
	MGame* _game;
	SquareState::Enum _state;
};

#endif // __BLANKSQUARE_H__
