#ifndef _GAMEMAP_H
#define _GAMEMAP_H

#include "grid.h"
#include "land.h"
#include "player.h"
#include <QObject>
#include <set>
#include <vector>
#include <ctime>
#include <cstdio>

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = 0);
    ~GameMap();
    Q_INVOKABLE QColor getColor(int index)const;
    Q_INVOKABLE void enter(int index);
    Q_INVOKABLE void exit(int index);
    Q_INVOKABLE void click(int index);
    Q_INVOKABLE void endTurn();
    Q_INVOKABLE int getDice(int index) const;
    Q_INVOKABLE void setDice(int index,int diceSum);
    void setColor(int index,QColor sColor);
    void AddGrid(Land *theLand,int row,int colum);
    void AssignLand(Player *theplayer, Land *theLand);
    void ChangeAttaker(Land* newLand);
signals:
    void sendColorChange(void);
public slots:
private:
    Grid grids[10][20];
    set<Land*> lands;
    vector<Player*> players;
    Land *attacker;
//    Land *attacked;
    Player *playerNow;
};

#endif // GAMEMAP_H
