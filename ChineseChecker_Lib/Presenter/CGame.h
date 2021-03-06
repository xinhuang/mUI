#ifndef __CGAME_H__
#define __CGAME_H__

class Board;
class Player;
class PieceGroup;
class Piece;

#include <mUI.h>
using mUI::System::Drawing::Point;

class CGame
{
public:
	static const int PieceGroupTotal = 6;

	CGame();
	~CGame();

	Board* get_Board();
	void set_Board(Board* board);

	virtual Piece* get_Picked();
	virtual void Pick(Piece* piece);

	PieceGroup* GetPieceGroup(int groupId);
	void SetPieceGroup(int groupId, PieceGroup* pieceGroup);

	void set_PlayerTotal(size_t playerTotal);
	void NewGame();

	Player* PlayerAt(size_t playerNumber);
	Player* get_CurrentPlayer();
    void set_PlayerGroupId(size_t playerNumber, int id);

protected:
	typedef std::map<size_t, vector<int>> PlayerIdMap;
	void CreatePlayers(const PlayerIdMap& idMap);
	void TakeTurn(int playerIndex);
	size_t get_CurrentPlayerIndex() const;


private:
	struct Data;
	Data* _d;
};

#endif // __CGAME_H__
