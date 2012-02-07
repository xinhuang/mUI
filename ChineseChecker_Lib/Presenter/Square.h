#ifndef __SQUARE_H__
#define __SQUARE_H__

class Piece;

class Square
{
public:
	bool get_IsOccupied() const { return false; }
	const Piece* get_Piece() const { return NULL; }
};

#endif // __SQUARE_H__
