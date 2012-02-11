#include "Player.h"

struct Player::Data
{
    vector<Color> colorList;
};

Player::Player( const vector<Color>& colorList ) : _d(new Data())
{
    _d->colorList = colorList;
}

Player::~Player()
{
    delete _d;
}

bool Player::Owns( const Color& color ) const
{
    return _d->colorList.end() != 
        find(_d->colorList.begin(), _d->colorList.end(), color);
}
