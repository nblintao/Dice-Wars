#include "gamemap.h"
using namespace std;

extern const int MAXDICE = 5;
const int playerAmount = 3;

GameMap::GameMap(QObject *parent) :
    QObject(parent)
{
    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            grids[i][j].setColor(QColor(255-i*10,200,255-j*10)); //get a more beautiful backgroud.
        }
    }
    srand((unsigned)time(NULL));

    for(int playerNumber=0;playerNumber<playerAmount;playerNumber++){
        Player *theplayer = new Player(playerNumber);            //set all players.
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
            fscanf(fp,"%c",&temp);          //get the map from the file.
        }
    }
    for (int index=1;index<30;index++){
        theLand=new Land;
        int nothing = 1;
        for (int i=0;i<10;i++){
            for (int j=0;j<20;j++){
                if (map[i][j]==index){
                    AddGrid(theLand,i,j);   //build each object of lands.
                    nothing = 0;
                }
            }
        }
        if(0 == nothing){
            AssignLand(players[rand()%playerAmount],theLand);
            theLand->setDice(rand()%MAXDICE + 1);
            lands.insert(theLand);            //determine the dice number randomly.
        }
    }

    FindAdjacent();

    for(int i=0;i<10;i++){
        for(int j=0;j<20;j++){
            Land *homeLand = grids[i][j].getLand();
            if(NULL != homeLand)              //set color for each players.
                grids[i][j].setColor(homeLand->getColor());
        }
    }

    attacker = NULL;
    attackerColor=attackedColor=QColor(255,255,255);
    diceAttacker="";
    diceAttacked="";
    playerNow = players[0];

}
void GameMap::AddGrid(Land *theLand,int row,int colum){
    theLand->AddGrid(&grids[row][colum]);
    grids[row][colum].setLand(theLand);
}

GameMap::~GameMap()        //the destructor of map
{
    for(set<Land*>::iterator it=lands.begin();it!=lands.end();it++){
        delete *it;
    }
    for(vector<Player*>::iterator it=players.begin();it!=players.end();it++){
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
        if((homeLand->BelongTo(playerNow))){  //when user click another land of himself, it means changing the attacker.
            if(homeLand->getDice() > 1)
                ChangeAttaker(homeLand);
                attackerColor=homeLand->getColor();
                diceAttacker="";
                diceAttacked="";
        }else{                         //when user click another land of others, it means attacking him.
            if((NULL != attacker) && (attacker->IsAdjacent(homeLand))){
                attackedColor=homeLand->getColor();
                attacker->Attack(homeLand,diceAttacker,diceAttacked);
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
QColor GameMap::getAttackerColor(){
    return attackerColor;
}
QColor GameMap::getAttackedColor(){
    return attackedColor;
}
QString GameMap::getAttackerDice(){
    return diceAttacker;
}
QString GameMap::getAttackedDice(){
    return diceAttacked;
}
QColor GameMap::getPlayerColor(){
    return playerNow->getColor();
}

void GameMap::endTurn(){
    ChangeAttaker(NULL);
    attackerColor=attackedColor=QColor(255,255,255);
    diceAttacker="";
    diceAttacked="";
    playerNow->AdjustMaxAdjacentLands();
    playerNow->AddDices();           //when a turn ends, dice numbers should be adjusted.
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

void GameMap::FindAdjacent(){    //find all the adjacent lands by going through the map.
    for (int i=0;i<9;i++)
        for (int j=0;j<19;j++)
        if (grids[i][j].getLand()!=0){               //check if two grids belong to different lands.
            if ((grids[i][j].getLand()!=grids[i+1][j].getLand())&&(grids[i+1][j].getLand()!=0)){
                grids[i][j].getLand()->AddAdjacent(grids[i+1][j].getLand());
                grids[i+1][j].getLand()->AddAdjacent(grids[i][j].getLand());   //set each other as adjacent.
            }
            if ((grids[i][j].getLand()!=grids[i][j+1].getLand())&&(grids[i][j+1].getLand()!=0)){
                grids[i][j].getLand()->AddAdjacent(grids[i][j+1].getLand());
                grids[i][j+1].getLand()->AddAdjacent(grids[i][j].getLand());
            }
        }
}
