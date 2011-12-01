#ifndef __SQUAREFACTORY_H__
#define __SQUAREFACTORY_H__

#include <vector>
using std::vector;

#include <mUI.h>
using mUI::System::Random;
using mUI::System::Drawing::Point;

class MGame;
class MineField;
class ISquare;

class SquareFactory
{
public:
	virtual vector<ISquare*> CreateSquares(MGame* game, MineField* mineField);
	virtual vector<bool> GenerateMineFieldMap(const Size& fieldSize, int mineTotal);

	static vector<ISquare*> CreateSquaresUsingFieldMap(MGame* game, MineField* mineField, const vector<bool>& fieldMap);

	static bool HasAdjacentMine(const vector<bool>& squareMap, const Size& fieldSize, size_t i);

	static bool IsMineUp		(const vector<bool>& fieldMap, const Size& fieldSize, int i);

	static bool IsMine( const vector<bool> &fieldMap, int i );
	static bool IsMineDown (const vector<bool>& fieldMap, const Size& fieldSize, int i);
	static bool IsMineLeft		(const vector<bool>& fieldMap, const Size& fieldSize, int i);
	static bool IsMineRight		(const vector<bool>& fieldMap, const Size& fieldSize, int i);
	static bool IsMineUpRight	(const vector<bool>& fieldMap, const Size& fieldSize, int i);
	static bool IsMineDownRight	(const vector<bool>& fieldMap, const Size& fieldSize, int i);
	static bool IsMineUpLeft	(const vector<bool>& fieldMap, const Size& fieldSize, int i);
	static bool IsMineDownLeft	(const vector<bool>& fieldMap, const Size& fieldSize, int i);

private:
	Random _random;
};

#endif // __SQUAREFACTORY_H__
