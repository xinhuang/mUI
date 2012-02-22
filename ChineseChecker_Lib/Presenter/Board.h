#ifndef __BOARDTEST_H__
#define __BOARDTEST_H__

class Square;

#include <mUI.h>
using mUI::System::Drawing::Point;

#include <vector>

class Board
{
public:
	static const int Width = 17;
	static const int Height = 17;

	Board();
	virtual ~Board();

	virtual std::vector<Square*> GetSquaresInFormation(const Point& goalLocation) const;
	virtual Square* SquareAt(const Point& location);

	virtual bool MovePiece(Square& from, Square& to);

protected:
	void InitializeGoalSquares();
	int GetSquareIndex(const Point& location) const;
	int GetSquareIndex(int x, int y) const;
	bool IsAccessible( const Square& from, const Square& to ) const;

	bool IsAdjacent( const Square &from, const Square &to ) const;

private:
	struct Data;
	Data* _d;
};

#endif // __BOARDTEST_H__
