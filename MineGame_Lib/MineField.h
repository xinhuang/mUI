#ifndef __MINEFIELD_H__
#define __MINEFIELD_H__

#include <mUI.h>
using mUI::System::Drawing::Size;

#include <vector>
using std::vector;

class MGame;
class ISquare;
class SquareFactory;

class MineField
{
public:
	MineField(MGame* game);
	virtual ~MineField();

	void ClearFields();
	const Size& get_Size() const;
	int get_MineTotal() const;

	ISquare* SquareAt(int row, int column);
	virtual void UncoverNeighborSquares(const ISquare& square) {}
	virtual int get_NeighborMineTotal(const ISquare* square) const { return 1; }
	void Refresh();


	int get_IndexMax() const;
	int get_Index(int row, int column) const;
	int get_RowFromIndex( int i );
	int get_ColumnFromIndex(int i) const;
	
	static int get_IndexMax(const Size& size);
	static int get_Index(const Size& fieldSize, int row, int column);
	static int get_RowFromIndex(const Size& size, int i);
	static int get_ColumnFromIndex(const Size& size, int i);

protected:
	SquareFactory* get_SquareFactory();
	void set_SquareFactory(SquareFactory* squareFactory);

private:
	MGame* _MGame;
	vector<ISquare*> _squares;
	SquareFactory* _squareFactory;
};

#endif // __MINEFIELD_H__
