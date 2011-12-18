#ifndef __SQUAREFACTORYFAKE_H__
#define __SQUAREFACTORYFAKE_H__

#include <gmock/gmock.h>

#include <Presenter/SquareFactory.h>

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

class SquareFactoryMock : public SquareFactory
{
public:
    MOCK_METHOD2(CreateSquares, vector<ISquare*>(MGame* game, MineField* mineField));
	MOCK_METHOD3(CreateSquares, vector<ISquare*>(MGame* game, MineField* mineField, const MineField::FieldMap&));
	MOCK_METHOD2(GenerateMineFieldMap, vector<bool>(const Size& fieldSize, 
		int mineTotal));
	MOCK_METHOD3(CreateSquaresUsingFieldMap, vector<ISquare*>(MGame* game, 
		MineField* mineField, const vector<bool>& fieldMap));
};

#endif	// __SQUAREFACTORYFAKE_H__
