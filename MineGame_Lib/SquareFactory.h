#ifndef __SQUAREFACTORY_H__
#define __SQUAREFACTORY_H__

#include <vector>
using std::vector;

#include <mUI.h>
using mUI::System::Random;

class MGame;
class MineField;
class ISquare;

class SquareFactory
{
public:
	virtual vector<ISquare*> CreateSquares(MGame* game, MineField* mineField);
	virtual vector<bool> GenerateMineFieldMap(const MineField& mineField);

	static int GetArrayIndexFromRowColumn(int r, int c, int rowWidth);

private:
	Random _random;
};

#endif // __SQUAREFACTORY_H__
