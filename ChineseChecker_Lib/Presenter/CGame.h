#ifndef __CGAME_H__
#define __CGAME_H__

class Board;
class Player;
class PieceGroup;

#include <mUI.h>
using mUI::System::Drawing::Color;

class CGame
{
public:
	static const int PieceGroupTotal = 6;

	CGame();
	~CGame();

	Board* get_Board();

	void set_PlayerTotal(size_t playerTotal);
	void NewGame();
	Player* PlayerAt(size_t playerNumber);
	Player* get_CurrentPlayer();
    void set_PlayerColor(size_t playerNumber, const Color& color);

	void MovePiece(const Point& from, const Point& to);

	PieceGroup* GetPieceGroup(int groupId);

protected:
	void TakeTurn(int playerIndex);
	size_t get_CurrentPlayerIndex() const;

private:
	struct Data;
	Data* _d;
};

#endif // __CGAME_H__
