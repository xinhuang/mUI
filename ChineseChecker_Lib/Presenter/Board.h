#ifndef __BOARDTEST_H__
#define __BOARDTEST_H__

class Square;

#include <mUI.h>
using mUI::System::Drawing::Point;

#include <vector>

class Board
{
public:
	Board();
	virtual ~Board();

	virtual std::vector<Square*> GetGoalSquares(const Point& goalLocation) const;

private:
	struct Data;
	Data* _d;
};

#endif // __BOARDTEST_H__
