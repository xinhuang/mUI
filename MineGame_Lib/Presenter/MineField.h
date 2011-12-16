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
	void set_Size(const Size& size);
	int get_MineTotal() const;
	void set_MineTotal(int mineTotal);

	ISquare* SquareAt(int x, int y);
	ISquare* SquareAt(const Point& location);
	ISquare* SquareAt(size_t i);
	virtual void UncoverAdjacent(const ISquare& square) {}
	void Refresh();

	int get_IndexMax() const;
	int get_Index(int x, int y) const;
	int get_Index(const Point& location) const;
	int get_YFromIndex( int i );
	int get_XFromIndex(int i) const;
	
	static int get_IndexMax(const Size& size);
	static int get_Index(const Size& fieldSize, int x, int y);
	static int get_YFromIndex(const Size& size, int i);
	static int get_XFromIndex(const Size& size, int i);

	int get_AdjacentMineTotal(const Point& location) const;

	bool IsMineAt( int i ) const;
	bool IsMineAt(int x, int y) const;

	SquareFactory* get_SquareFactory();
	void set_SquareFactory(SquareFactory* squareFactory);
	void set_Width( int width );
	void set_Height( int height );

private:
	MGame* _game;
	vector<ISquare*> _squares;
	SquareFactory* _squareFactory;
	Size _size;
	int _mineTotal;
};

#endif // __MINEFIELD_H__
