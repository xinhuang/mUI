#ifndef __SQUAREFACTORY_H__
#define __SQUAREFACTORY_H__

#include <vector>
using std::vector;

class MGame;
class MineField;
class ISquare;

class SquareFactory
{
public:
	virtual vector<ISquare*> CreateSquares(MGame* game, MineField* mineField);
};

#endif // __SQUAREFACTORY_H__
