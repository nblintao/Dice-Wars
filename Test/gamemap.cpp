#include "gamemap.h"

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            grids[i][j].setColor(QColor(i*10,j*10,0));
        }
    }
}

QColor GameMap::getColor(int index) const
{
    return grids[index/20][index%20].getColor();
}

void GameMap::enter(int index){
    setColor(index, QColor(Qt::blue));
}

void GameMap::setColor(int index, QColor sColor){
    grids[index/20][index%20].setColor(sColor);
}


