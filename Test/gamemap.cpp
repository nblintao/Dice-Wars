#include "gamemap.h"

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            grids[i][j].setColor(QColor(i*10,j*10,0));
        }
    }

    Land& newLand = new Land;
    AddGrid(newLand,0,1);
    AddGrid(newLand,0,2);
    AddGrid(newLand,0,3);
    AddGrid(newLand,1,2);
    AddGrid(newLand,1,3);
    AddGrid(newLand,2,3);
    lands.insert(newLand);
}
void GameMap::AddGrid(Grid& newLand,int row,int colum){
    newLand.AddGrid(grids[row][colum]);
    grids[row][colum].setLand(newLand);
}

GameMap::~GameMap()
{
    for(set<Land&>::iterator it=lands.begin();it!=lands.end();it++){
        delete it;
    }
}

QColor GameMap::getColor(int index) const
{
    return grids[index/20][index%20].getColor();
}

void GameMap::enter(int index){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(homeLand)
        homeLand->setColor(homeLand.color.lighter(80));
}

void GameMap::exit(int index){
    Land& homeLand = grids[index/20][index%20].getLand();
    if(homeLand)
        homeLand->setColor(homeLand.color);
}

