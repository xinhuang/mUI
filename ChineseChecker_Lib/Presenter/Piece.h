#ifndef __PIECE_H__
#define __PIECE_H__

class Square;

class Piece
{
public:
	virtual const Square* get_Square() const { return 0; }
	virtual Square* get_Square() { return 0; }
};

#endif // __PIECE_H__
