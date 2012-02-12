#include "Player.h"

struct Player::Data
{
    vector<int> colorList;
};

Player::Player( const vector<int>& colorList ) : _d(new Data())
{
    _d->colorList = colorList;
}

Player::~Player()
{
    delete _d;
}

bool Player::Owns( int color ) const
{
    return _d->colorList.end() != 
        find(_d->colorList.begin(), _d->colorList.end(), color);
}
