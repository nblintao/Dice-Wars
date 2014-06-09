#ifndef _LAND_H
#define _LAND_H

//#include "Player.h"
#include "Grid.h"
#include <set>
using namespace std;

class Land
{
private:
    //Player& owner;
    set<Grid> grids;
    set<Land&> adjacentLands;

public:
    Land();
    ~Land();
    bool IsAdjacent(Land& anotherLand);
};

#endif