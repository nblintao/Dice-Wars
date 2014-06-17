#include "gamemap.h"

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
//    for(int i=0;i<10;i++){
//        for(int j=0;j<20;j++){
//            grids[i][j].setColor(QColor(i*10,j*10,0));
//        }
//    }

    Land *theLand;
    theLand = new Land;
    AddGrid(theLand,0,1);
    AddGrid(theLand,0,2);
    AddGrid(theLand,0,3);
    AddGrid(theLand,1,2);
    AddGrid(theLand,1,3);
    AddGrid(theLand,2,3);
    lands.insert(theLand);

    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            Land *homeLand = grids[i][j].getLand();
            if(NULL != homeLand)
                grids[i][j].setColor(homeLand->getColor());
        }
    }
}
void GameMap::AddGrid(Land *theLand,int row,int colum){
    theLand->AddGrid(&grids[row][colum]);
    grids[row][colum].setLand(theLand);
}

GameMap::~GameMap()
{
    for(set<Land*>::iterator it=lands.begin();it!=lands.end();it++){
        delete *it;
    }
}

QColor GameMap::getColor(int index) const
{
    return grids[index/20][index%20].getColor();
}

void GameMap::enter(int index){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(homeLand)
        homeLand->Enter();

}

void GameMap::exit(int index){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(homeLand)
        homeLand->Exit();
}

