#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Piece.h"

#include <mUI.h>
using mUI::System::Drawing::Point;
using mUI::System::Forms::MouseEventArgs;

class CGame;

class Square
{
public:
	Square(CGame* game, const Point& location);
	virtual ~Square();

	virtual Piece* get_Piece();
	virtual const Piece* get_Piece() const;

	virtual const Point& get_Location() const;

protected:
	virtual void OnMouseClick(void* sender, MouseEventArgs* e);
	virtual void set_Piece(Piece* piece);

private:
	friend void Piece::MoveTo(Square*);

private:
	struct Data;
	Data* _d;
};

#endif // __SQUARE_H__
