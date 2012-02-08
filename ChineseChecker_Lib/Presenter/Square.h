#ifndef __SQUARE_H__
#define __SQUARE_H__

class Piece;

class Square
{
public:
	Square();
	virtual ~Square();

	const Piece* get_Piece() const;
	virtual void set_Piece(Piece* piece);

private:
	struct Data;
	Data* _d;
};

#endif // __SQUARE_H__
