#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <mUI.h>
using mUI::System::Drawing::Color;

class Player
{
public:
    Player(const vector<int>& colorList);
    virtual ~Player();

	bool Owns(int color) const;

private:
    struct Data;
    Data* _d;
};

#endif // __PLAYER_H__
