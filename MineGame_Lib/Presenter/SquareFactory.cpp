#include "SquareFactory.h"

#include "NumberSquare.h"
#include "BlankSquare.h"
#include "MineSquare.h"
#include "MineField.h"

#include <algorithm>
using std::swap;

#include <mUI.h>
using mUI::System::Drawing::Point;

vector<ISquare*> SquareFactory::CreateSquares( MGame* game, MineField* mineField, const MineField::FieldMap& fieldMap )
{
    vector<ISquare*> squares;
    for (size_t y = 0; y < fieldMap.size(); ++y)
    {
        for (size_t x = 0; x < fieldMap[y].size(); ++x)
        {
            ISquare* square;
            if (fieldMap[y][x])
            {
                square = new MineSquare(game, mineField, x, y);
            }
            else
            {
                if (HasAdjacentMine(fieldMap, x, y))
                    square = new NumberSquare(game, mineField, x, y);
                else
                    square = new BlankSquare(game, mineField, x, y);
            }
            squares.push_back(square);
        }
    }
    return squares;
}

bool SquareFactory::HasAdjacentMine( const MineField::FieldMap& squareMap, int x, int y )
{
    return HasMine(squareMap, x - 1,    y - 1)
        || HasMine(squareMap, x - 1,    y)
        || HasMine(squareMap, x - 1,    y + 1)
        || HasMine(squareMap, x,        y - 1)
        || HasMine(squareMap, x,        y + 1)
        || HasMine(squareMap, x + 1,    y - 1)
        || HasMine(squareMap, x + 1,    y)
        || HasMine(squareMap, x + 1,    y + 1);
}

bool SquareFactory::HasMine( const MineField::FieldMap& squareMap, size_t x, size_t y )
{
    if (y < 0 || y >= squareMap.size())
        return false;
    if (x < 0 || x >= squareMap[y].size())
        return false;
    return squareMap[y][x];
}
