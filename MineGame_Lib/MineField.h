#ifndef __MINEFIELD_H__
#define __MINEFIELD_H__

#include <mUI.h>
using mUI::System::Drawing::Size;

#include <vector>
using std::vector;

class MGame;
class ISquare;

class MineField
{
public:
	MineField(MGame* game);
	virtual ~MineField();

	const Size& get_Size() const;
	int get_MineTotal() const;

	ISquare* SquareAt(int row, int column);
	virtual void UncoverNeighborSquares(const ISquare& square) {}

protected:
	virtual void CreateSquares();

private:
	MGame* _MGame;
	vector<ISquare*> _squares;
};

#endif // __MINEFIELD_H__
