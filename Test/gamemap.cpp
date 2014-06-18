#include "gamemap.h"
using namespace std;

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            grids[i][j].setColor(QColor(255-i*10,200,255-j*10));
        }
    }
    srand((unsigned)time(NULL));

    int const playerAmount = 2;
    for(int playerNumber=0;playerNumber<playerAmount;playerNumber++){
        Player *theplayer = new Player(playerNumber);
        players.push_back(theplayer);
    }



    Land *theLand;

    int map[10][20];
    char temp;
    FILE *fp=fopen("c.csv","r");
    if (fp!=NULL){
        for (int i=0;i<10;i++)
        for (int j=0;j<20;j++){
            fscanf(fp,"%d",&map[i][j]);
            fscanf(fp,"%c",&temp);
        }
    }
    for (int index=1;index<30;index++){
        theLand=new Land;
        int nothing = 1;
        for (int i=0;i<10;i++){
            for (int j=0;j<20;j++){
                if (map[i][j]==index){
                    AddGrid(theLand,i,j);
                    nothing = 0;
                }
            }
        }
        if(0 == nothing){
            AssignLand(players[rand()%playerAmount],theLand);
            theLand->setDice(rand()%MAXDICE + 1);
            lands.insert(theLand);
        }
    }


/*
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
*/

    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            Land *homeLand = grids[i][j].getLand();
            if(NULL != homeLand)
                grids[i][j].setColor(homeLand->getColor());
        }
    }

    attacker = NULL;

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
        ChangeAttaker(NULL);
    }else{
        if((homeLand->BelongTo(playerNow))){
            if(homeLand->getDice() > 1)
                ChangeAttaker(homeLand);
        }else{
            if((NULL != attacker) && (attacker->IsAdjacent(homeLand))){
                attacker->Attack(homeLand);
                ChangeAttaker(NULL);
            }
        }
    }
}
void GameMap::ChangeAttaker(Land* newLand){
    if(NULL != attacker){
        attacker->setColor(attacker->getColor());
    }
    if(NULL != newLand){
        attacker = newLand;
        attacker->setColor(Qt::black);
    }
}

void GameMap::endTurn(){
    ChangeAttaker(NULL);
    playerNow->AdjustMaxAdjacentLands();
    playerNow->AddDices();
    int index = playerNow->GetID();
    do{        
        index++;
        if(index >= (int) players.size())
            index=0;
    }while(!players[index]->IsAlive());
    if(playerNow == players[index]){
        cout<<"GAME OVER! PLAYER "<<index<<" WIN!"<<endl;
    }else{
        playerNow = players[index];
    }
}

void GameMap::AssignLand(Player *thePlayer, Land *theLand){
    thePlayer->AddLand(theLand);
    theLand->ChangeOwner(thePlayer);
}

