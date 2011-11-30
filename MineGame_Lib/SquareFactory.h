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
	virtual vector<bool> GenerateMineFieldMap(const MineField& mineField);

	static bool HasAdjacentMine( const vector<bool>& squareMap, const Size& fieldSize, size_t i );
	static bool IsMineUp( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineDown( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineLeft( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineRight( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineUpRight( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineDownRight( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineUpLeft( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );
	static bool IsMineDownLeft( const vector<bool>& fieldMap, const Size& fieldSize, size_t i );

private:
	Random _random;
};

#endif // __SQUAREFACTORY_H__
