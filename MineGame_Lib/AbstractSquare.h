#ifndef __ABSTRACTORSQUARE_H__
#define __ABSTRACTORSQUARE_H__

#include "ISquare.h"

class MGame;
class MineField;

class AbstractSquare : public ISquare
{
public:
	AbstractSquare(MGame* game, MineField* mineField, int row, int column);

	SquareState::Enum get_State() const;
	int get_Row() const { return _row; }
	int get_Column() const { return _column; }

protected:
	void set_State(SquareState::Enum state);

private:
	SquareState::Enum _state;
	int _row, _column;
};

#endif // __ABSTRACTORSQUARE_H__
