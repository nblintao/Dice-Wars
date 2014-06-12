#ifndef _LAND_H
#define _LAND_H

#include "Grid.h"
#include "Player.h"
#include <iostream>
#include <set>
using namespace std;

//class Player;

class Land
{
private:
    Player& owner;
    set<Grid> grids;
    set<Land&> adjacentLands;
    int diceAmount;

public:
    Land();
    ~Land();
    bool IsAdjacent(Land& anotherLand);
    void Attack(Land& attacked);
    void ChangeOwner(Player& newOwner);
};

#endif