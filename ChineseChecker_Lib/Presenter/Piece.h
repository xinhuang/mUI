#ifndef __PIECE_H__
#define __PIECE_H__

class Square;
class Board;

class Piece
{
public:
	Piece(Board* board, int id);
	virtual ~Piece();

	virtual const Square* get_Square() const;
	virtual Square* get_Square();
	virtual int get_Id() const;

	virtual bool MoveTo(Square* square);

private:
	struct Data;
	Data* _d;
};

#endif // __PIECE_H__
