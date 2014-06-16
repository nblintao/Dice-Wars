#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "grid.h"
#include "land.h"
#include <QObject>
#include <set>


class GameMap : public QObject
{
    Q_OBJECT

public:
    explicit GameMap(QObject *parent = 0);
    Q_INVOKABLE QColor getColor(int index)const;
    Q_INVOKABLE void enter(int index);
    void setColor(int index,QColor sColor);
    void AddGrid(Grid& newGrid,int row,int colum);
signals:
    void sendColorChange(void);
public slots:
private:
    Grid grids[10][20];
    set<Land&> lands;
};

#endif // GAMEMAP_H
