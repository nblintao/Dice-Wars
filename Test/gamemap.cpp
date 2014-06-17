#include "gamemap.h"
using namespace std;

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
//    for(int i=0;i<10;i++){
//        for(int j=0;j<20;j++){
//            grids[i][j].setColor(QColor(i*10,j*10,0));
//        }
//    }
    srand((unsigned)time(NULL));

    int const playerAmount = 2;
    for(int playerNumber=0;playerNumber<playerAmount;playerNumber++){
        Player *theplayer = new Player(playerNumber);
        players.push_back(theplayer);
    }

    int const MAXDICE = 6;

    Land *theLand;

    theLand = new Land;
    AddGrid(theLand,0,1);
    AddGrid(theLand,0,2);
    AddGrid(theLand,0,3);
    AddGrid(theLand,1,2);
    AddGrid(theLand,1,3);
    AddGrid(theLand,2,3);
    AssignLand(players[rand()%playerAmount],theLand);
    theLand->setDice(rand()%MAXDICE + 1);
    lands.insert(theLand);

    theLand = new Land;
    AddGrid(theLand,0,4);
    AddGrid(theLand,0,5);
    AddGrid(theLand,0,6);
    AddGrid(theLand,1,5);
    AddGrid(theLand,1,6);
    AddGrid(theLand,2,6);
    AssignLand(players[rand()%playerAmount],theLand);
    theLand->setDice(rand()%MAXDICE + 1);
    lands.insert(theLand);

    theLand = new Land;
    AddGrid(theLand,3,1);
    AddGrid(theLand,3,2);
    AddGrid(theLand,3,3);
    AddGrid(theLand,3,4);
    AddGrid(theLand,2,4);
    AddGrid(theLand,2,5);
    AssignLand(players[rand()%playerAmount],theLand);
    theLand->setDice(rand()%MAXDICE + 1);
    lands.insert(theLand);


    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            Land *homeLand = grids[i][j].getLand();
            if(NULL != homeLand)
                grids[i][j].setColor(homeLand->getColor());
        }
    }

    attacker = NULL;
    attacked = NULL;

    playerNow = players[0];

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
int GameMap::getDice(int index) const
{
    return grids[index/20][index%20].getDice();
}
void GameMap::setDice(int index,int diceSum){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(homeLand)
        homeLand->setDice(diceSum);
}

void GameMap::enter(int index){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(homeLand && (homeLand != attacker))
        homeLand->Enter();

}

void GameMap::exit(int index){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(homeLand && (homeLand != attacker))
        homeLand->Exit();
}

void GameMap::click(int index){
    Land *homeLand = grids[index/20][index%20].getLand();
    if(NULL == homeLand){
        attacker = attacked = NULL;
    }else{
        if(homeLand->BelongTo(playerNow)){
            if(NULL != attacker)
                attacker->setColor(attacker->getColor());
            attacker = homeLand;
            attacker->setColor(Qt::black);
            attacked = NULL;
        }else{
            if(NULL != attacker){
                attacked = homeLand;
                attacker->Attack(attacked);
                attacker->setColor(attacker->getColor());
                attacker = attacked = NULL;
            }
        }
    }
}
void GameMap::endTurn(){

}

void GameMap::AssignLand(Player *thePlayer, Land *theLand){
    thePlayer->AddLand(theLand);
    theLand->ChangeOwner(thePlayer);
}

