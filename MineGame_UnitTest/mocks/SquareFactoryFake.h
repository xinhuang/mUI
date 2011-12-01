#ifndef __SQUAREFACTORYFAKE_H__
#define __SQUAREFACTORYFAKE_H__

#include <SquareFactory.h>

class SquareFactoryFake : public SquareFactory
{
public:
	SquareFactoryFake()	{}
	SquareFactoryFake(const vector<bool>& presetMap) : _presetMap(presetMap)
	{}

	virtual vector<bool> GenerateMineFieldMap(const Size& fieldSize, int mineTotal)
	{
		return _presetMap;
	}

private:
	vector<bool> _presetMap;
};

#endif	// __SQUAREFACTORYFAKE_H__
