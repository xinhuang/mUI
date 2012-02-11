#ifndef __PIECEGROUP_H__
#define __PIECEGROUP_H__

class Piece;
class Square;
class Board;

#include <vector>

#include <mUI.h>
using mUI::System::Drawing::Point;

class PieceGroup
{
public:
	static const int PieceMax = 15;

	PieceGroup(int id, Board* board, 
		const Point& fromLocation, const Point& goalLocation);

	void CreatePieces( int pieceTotal );

	virtual ~PieceGroup();

	virtual int get_Id() const;
	virtual std::vector<Piece*>& get_Pieces();
	virtual std::vector<Square*> get_StartSquares();

private:
	struct Data;
	Data* _d;
};

#endif // __PIECEGROUP_H__
