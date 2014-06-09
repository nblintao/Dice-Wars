#ifndef _PLAYER_H
#define _PLAYER_H

#include "Land.h"
#include <set>
using namespace std;

class Player
{
private:
    set<Land&> lands;
    int color;
    int maxAdjacentLands;
    int remainDices;
public:
    Player();
    ~Player();
};
#endif
