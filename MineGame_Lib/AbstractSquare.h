#ifndef __ABSTRACTORSQUARE_H__
#define __ABSTRACTORSQUARE_H__

#include "ISquare.h"

class MGame;
class MineField;

class AbstractSquare : public ISquare
{
public:
	AbstractSquare(MGame* game, MineField* mineField, int row, int column);

	virtual SquareState::Enum get_State() const;
	virtual int get_Row() const { return _row; }
	virtual int get_Column() const { return _column; }
	virtual void ToggleFlag();
	virtual bool HasMine() const { return false; }

protected:
	void set_State(SquareState::Enum state);
	MGame* get_Game();
	MineField* get_MineField();
	const MGame* get_Game() const;
	const MineField* get_MineField() const;

private:
	SquareState::Enum _state;
	int _row, _column;
	MGame* _game;
	MineField* _mineField;
};

#endif // __ABSTRACTORSQUARE_H__
