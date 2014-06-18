#ifndef _LAND_H
#define _LAND_H

#include "Grid.h"
#include "Player.h"
#include <iostream>
#include <set>
#include <QColor>
#include <queue>
using namespace std;

int const MAXDICE = 3;

class Player;
class Grid;
class Land
{
private:
    Player *owner;
    set<Grid*> grids;
    set<Land*> adjacentLands;
    int diceAmount;
    QColor color;

public:
    Land();
    ~Land();
    bool IsAdjacent(Land *anotherLand);
    int AdjacentLandsNumber();
    void Attack(Land *attacked);
    void ChangeOwner(Player *newOwner);
    void AddGrid(Grid* newGrid);
    void setColor(QColor color);
    void setDice(int diceSum);
    int getDice(){return diceAmount;}
    void Enter();
    void Exit();
    QColor getColor(){return color;}
    bool BelongTo(Player *owner){return this->owner==owner;}
    void AddAdjacent(Land *anotherLand){
        adjacentLands.insert(anotherLand);
    }

};
#endif
