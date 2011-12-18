#ifndef __SQUAREFACTORY_H__
#define __SQUAREFACTORY_H__

#include <vector>
using std::vector;

#include <mUI.h>
using mUI::System::Random;
using mUI::System::Drawing::Point;

class MGame;
class ISquare;
#include "MineField.h"

class SquareFactory
{
public:
    virtual vector<ISquare*> CreateSquares(MGame* game, MineField* mineField, const MineField::FieldMap& fieldMap);
    bool HasAdjacentMine(const MineField::FieldMap& squareMap, int x, int y);
    bool HasMine( const MineField::FieldMap& squareMap, size_t x, size_t y );
};

#endif // __SQUAREFACTORY_H__
