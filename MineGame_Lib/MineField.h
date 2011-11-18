#ifndef __MINEFIELD_H__
#define __MINEFIELD_H__

#include <mUI.h>

using mUI::System::Drawing::Size;

class MGame;
class ISquare;

class MineField
{
public:
	MineField(MGame* game);

	const Size& get_Size() const;
	int get_MineTotal() const;

	ISquare* SquareAt(int row, int column);
	virtual void UncoverNeighborSquares(const ISquare& square) {}

private:
	MGame* _MGame;
};

#endif // __MINEFIELD_H__
