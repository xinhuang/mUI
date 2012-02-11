#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <mUI.h>
using mUI::System::Drawing::Color;

class Player
{
public:
    bool Owns(const Color& color) const;
};

#endif // __PLAYER_H__
