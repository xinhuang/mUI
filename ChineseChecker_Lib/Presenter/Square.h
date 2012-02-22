#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Piece.h"

#include <mUI.h>
using mUI::System::Drawing::Point;

class Square
{
public:
	Square(const Point& location);
	virtual ~Square();

	virtual Piece* get_Piece();
	virtual const Piece* get_Piece() const;

	virtual const Point& get_Location() const;

private:
	friend void Piece::MoveTo(Square*);
	virtual void set_Piece(Piece* piece);

private:
	struct Data;
	Data* _d;
};

#endif // __SQUARE_H__
