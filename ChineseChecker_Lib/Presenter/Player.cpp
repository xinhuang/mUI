#include "Player.h"

bool Player::Owns( const Color& color ) const
{
    return color == Color::Black;
}
