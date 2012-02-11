#ifndef __PIECEGROUP_H__
#define __PIECEGROUP_H__

class Piece;

#include <vector>

class PieceGroup
{
public:
	static const int PieceMax = 15;

	PieceGroup(int id);

	void CreatePieces( int pieceTotal );

	virtual ~PieceGroup();

	virtual int get_Id() const;
	virtual std::vector<Piece*>& get_Pieces();

private:
	struct Data;
	Data* _d;
};

#endif // __PIECEGROUP_H__
