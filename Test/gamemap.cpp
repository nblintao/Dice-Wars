#include "gamemap.h"
using namespace std;

extern const int MAXDICE = 5;
extern const int ROW = 20;
extern const int COLUMN = 40;
const int LANDMAX = 30;

GameMap::GameMap(QObject *parent) :  QObject(parent){
    playerAmount = 2;
    status = 0;
}

void GameMap::initialize(){
    status = 1;
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COLUMN;j++){ 
            grids[i][j].setColor(QColor(255-i*50/ROW,255-i*50/ROW,255-j*10/ROW)); //get a more beautiful backgroud.
        }
    }
    srand((unsigned)time(NULL));
    for(int playerNumber=0;playerNumber<playerAmount;playerNumber++){
        Player *theplayer = new Player(playerNumber);            //set all players.
        players.push_back(theplayer);
    }
    Land *theLand;
    int map[ROW][COLUMN];
    char temp;
    FILE *fp=fopen("20_40_B.csv","r");
    if (fp!=NULL){
        for (int i=0;i<ROW;i++)
            for (int j=0;j<COLUMN;j++){
                fscanf(fp,"%d",&map[i][j]);
                fscanf(fp,"%c",&temp);          //get the map from the file.
            }
    }else{
        std::cout<<"Load file failed"<<endl;
    }
    for (int index=1;index<LANDMAX;index++){
        theLand=new Land;
        int nothing = 1;
        for (int i=0;i<ROW;i++){
            for (int j=0;j<COLUMN;j++){
                if (map[i][j]==index){
                    AddGrid(theLand,i,j);   //build each object of lands.
                    nothing = 0;
                }
            }
        }
        if(0 == nothing){
            AssignLand(players[rand()%playerAmount],theLand);
            theLand->SetDice(rand()%MAXDICE + 1);
            lands.insert(theLand);            //determine the dice number randomly.
        }
    }
    FindAdjacent();
    for(int i=0;i<ROW;i++){
        for(int j=0;j<COLUMN;j++){
            Land *homeLand = grids[i][j].getLand();
            if(NULL != homeLand)              //set color for each players.
                grids[i][j].setColor(homeLand->GetColor());
        }
    }
    attacker = NULL;
    attackerColor=attackedColor=QColor(255,255,255);
    diceAttacker="";
    diceAttacked="";
    playerNow = players[0];
    std::cout<<"Initial succeed."<<endl;
}

void GameMap::gameOver(){
    status = 2;
    for(set<Land*>::iterator it=lands.begin();it!=lands.end();it++){
        delete *it;
    }
    for(vector<Player*>::iterator it=players.begin();it!=players.end();it++){
        delete *it;
    }
    lands.clear();
    players.clear();
}

void GameMap::AddGrid(Land *theLand,int row,int colum){
    theLand->AddGrid(&grids[row][colum]);
    grids[row][colum].setLand(theLand);
}

void GameMap::setDice(int index,int diceSum){
    Land *homeLand = grids[index/COLUMN][index%COLUMN].getLand();
    if(homeLand)
        homeLand->SetDice(diceSum);
}

void GameMap::enter(int index){
    Land *homeLand = grids[index/COLUMN][index%COLUMN].getLand();
    if(homeLand && (homeLand != attacker))
        homeLand->Enter();
}

void GameMap::exit(int index){
    Land *homeLand = grids[index/COLUMN][index%COLUMN].getLand();
    if(homeLand && (homeLand != attacker))
        homeLand->Exit();
}

void GameMap::click(int index){
    Land *homeLand = grids[index/COLUMN][index%COLUMN].getLand();
    diceAttacker="";
    diceAttacked="";
    attackerColor=QColor(255,255,255);
    attackedColor=QColor(255,255,255);
    if(NULL == homeLand){
        ChangeAttaker(NULL);
    }else{
        if((homeLand->BelongTo(playerNow))){  //when user click another land of himself, it means changing the attacker.
            if(homeLand->GetDice() > 1)
                ChangeAttaker(homeLand);                
        }else{                         //when user click another land of others, it means attacking him.
            if((NULL != attacker) && (attacker->IsAdjacent(homeLand))){
                attackedColor=homeLand->GetColor();
                attackerColor=attacker->GetColor();
                attacker->Attack(homeLand,diceAttacker,diceAttacked);
                ChangeAttaker(NULL);
            }
        }
    }
    if(IsLastPlayer())
        gameOver();
}

void GameMap::ChangeAttaker(Land* newLand){
    if(NULL != attacker){
        attacker->SetColor(attacker->GetColor());
    }
    if(NULL != newLand){
        attacker = newLand;
        attacker->SetColor(Qt::black);
    }else{
        attacker = NULL;
    }
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
    playerNow = players[index];
}

void GameMap::AssignLand(Player *thePlayer, Land *theLand){
    thePlayer->AddLand(theLand);
    theLand->ChangeOwner(thePlayer);
}

void GameMap::FindAdjacent(){    //find all the adjacent lands by going through the map.
    for (int i=0;i<ROW-1;i++)
        for (int j=0;j<COLUMN-1;j++)
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

bool GameMap::IsLastPlayer(){
    int aliveNumber = 0;
    for(vector<Player*>::iterator it=players.begin();it!=players.end();it++){
        Player *theplayer = *it;
        if(theplayer->IsAlive()){
            aliveNumber++;
            alivePlayer = theplayer;
        }
    }
    return aliveNumber==1;
}
