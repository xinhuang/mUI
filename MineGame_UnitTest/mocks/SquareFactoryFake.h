#ifndef __SQUAREFACTORYFAKE_H__
#define __SQUAREFACTORYFAKE_H__

#include <SquareFactory.h>

class SquareFactoryFake : public SquareFactory
{
public:
	virtual vector<ISquare*> CreateSquares(MGame* game, MineField* mineField)
	{
		return vector<ISquare*>();
	}

	virtual vector<bool> GenerateMineFieldMap(const MineField& mineField)
	{
		return vector<bool>();
	}
};

#endif	// __SQUAREFACTORYFAKE_H__
