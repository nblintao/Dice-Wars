#ifndef _LAND_H
#define _LAND_H

#include "Grid.h"
//#include "Player.h"
#include <iostream>
#include <set>
#include <QColor>
using namespace std;

//class Player;
class Grid;
class Land
{
private:
    //Player& owner;
    set<Grid*> grids;
//    set<Land&> adjacentLands;
//    int diceAmount;
    QColor color;

public:
    Land();
    ~Land();
//    bool IsAdjacent(Land& anotherLand);
//    void Attack(Land& attacked);
//    void ChangeOwner(Player& newOwner);
    void AddGrid(Grid* newGrid);
    void setColor(QColor color);
    void Enter();
    void Exit();
};

#endif
