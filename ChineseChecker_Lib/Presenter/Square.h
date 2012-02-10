#ifndef __SQUARE_H__
#define __SQUARE_H__

class Piece;

#include <mUI.h>
using mUI::System::Drawing::Point;

class Square
{
public:
	Square(const Point& location);
	virtual ~Square();

	virtual const Piece* get_Piece() const;
	virtual void set_Piece(Piece* piece);

	virtual const Point& get_Location() const;

private:
	struct Data;
	Data* _d;
};

#endif // __SQUARE_H__
