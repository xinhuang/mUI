#ifndef __ABSTRACTORSQUARE_H__
#define __ABSTRACTORSQUARE_H__

#include "ISquare.h"
#include "../View/View.h"

class MGame;
class MineField;

class AbstractSquare : public ISquare
{
public:
	AbstractSquare(MGame* game, MineField* mineField, const Point& location);

	virtual void Bind(ISquareView* view);
	virtual SquareState::Enum get_State() const;
	virtual int get_X() const { return _location.X; }
	virtual int get_Y() const { return _location.Y; }
	virtual const Point& get_Location() const { return _location; }
	virtual void ToggleFlag();
	virtual bool HasMine() const { return false; }

protected:
	void set_State(SquareState::Enum state);
	MGame* get_Game();
	MineField* get_MineField();
	const MGame* get_Game() const;
	const MineField* get_MineField() const;
	ISquareView* get_View();

	void set_ViewState( SquareViewState::Enum state );

private:
	SquareState::Enum _state;
	const Point _location;
	MGame* _game;
	MineField* _mineField;
	ISquareView* _view;
};

#endif // __ABSTRACTORSQUARE_H__
