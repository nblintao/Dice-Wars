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
    void setColor(int index,QColor sColor);
    void AddGrid(Land *theLand,int row,int colum);
    void AssignLand(Player *theplayer, Land *theLand);
signals:
    void sendColorChange(void);
public slots:
private:
    Grid grids[10][20];
    set<Land*> lands;
    vector<Player*> players;
};

#endif // GAMEMAP_H
