#include "gamemap.h"
#include <stdio.h>

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            grids[i][j].setColor(QColor(i*10,j*10,0));
        }
    }
    /*int map[10][20]={0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};*/
    int map[10][20];
    FILE *fp;
    fp=fopen("map1.txt","r");
    for (int i=0;i<10;i++)
    for (int j=0;j<20;j++)
        fscanf(fp,"%d",&map[i][j]);

    for (int index=1;index<20;index++){
        Land *theLand;
        theLand=new Land;
        for (int i=0;i<10;i++)
        for (int j=0;j<20;j++)
            if (map[i][j]==index)
                AddGrid(theLand,i,j);
       lands.insert(theLand);
    }
    /*Land *theLand;
    theLand = new Land;
    AddGrid(theLand,0,1);
    AddGrid(theLand,0,2);
    AddGrid(theLand,0,3);
    AddGrid(theLand,1,2);
    AddGrid(theLand,1,3);
    AddGrid(theLand,2,3);
    lands.insert(theLand);*/
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


