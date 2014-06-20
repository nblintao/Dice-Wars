#include "Land.h"


Land::Land()
{
    owner = NULL;
    color = QColor(Qt::yellow);
    //setDice(rand()%MAXDICE + 1);
    //diceAmount = rand()%MAXDICE + 1;
}


Land::~Land()
{
}

bool Land::IsAdjacent(Land *anotherLand)
{
    return adjacentLands.count(anotherLand);   //judge whether two lands are adjacent.
}

void Land::Attack(Land *attacked,QString& diceAttacker,QString& diceAttacked)
{
    int attackerDots, attackedDots;
    int dots;
    QString tmpString;
    attackerDots = 0;
    attackedDots = 0;
    diceAttacker="";
    diceAttacked="";
    std::cout << "attacker: " << endl;
    for (int i = 0; i < this->diceAmount; i++) {  //give each dice the number they show.
        dots = rand() % 6 + 1;
        std::cout << dots << endl;
        attackerDots += dots;
        if(0==i){
            diceAttacker.setNum(dots);
        }
        else{
            tmpString.setNum(dots);
            diceAttacker=diceAttacker+" + "+tmpString;
        }
    }
    tmpString.setNum(attackerDots);
    diceAttacker=diceAttacker+" = "+tmpString;
    std::cout << "=" << attackerDots << endl;

    std::cout << "attacked: " << endl;
    for (int i = 0; i < attacked->diceAmount; i++) {
        dots = rand() % 6 + 1;
        std::cout << dots << endl;
        attackedDots += dots;
        if(0==i){
            diceAttacked.setNum(dots);
        }
        else{
            tmpString.setNum(dots);
            diceAttacked=diceAttacked+" + "+tmpString;
        }
    }
    tmpString.setNum(attackedDots);
    diceAttacked=diceAttacked+" = "+tmpString;
    std::cout << "=" << attackedDots << endl;
    if (attackerDots>attackedDots) {           //if the attack is a success.
        attacked->ChangeOwner(this->owner);
        //attacked->diceAmount = this->diceAmount - 1;
        attacked->setDice(this->diceAmount - 1);
        //this->diceAmount = 1;
        setDice(1);
    }
    else {                                   //if the attack is a failure.
        //this->diceAmount = 1;
        setDice(1);
    }
}

int Land::AdjacentLandsNumber(){          //count adjacent number to determine how much dices will be added.
    queue<Land*> landQueue1;
    set<Land*> connectedLands;
    landQueue1.push(this);
    connectedLands.insert(this);
    while(!landQueue1.empty()){
        Land *theLand;
        theLand = landQueue1.front();
        for(set<Land*>::iterator it=theLand->adjacentLands.begin();it!=theLand->adjacentLands.end();it++){
            if((connectedLands.count(*it)==0) && ((*it)->owner == owner)){
                landQueue1.push(*it);
                connectedLands.insert(*it);
            }
        }
        landQueue1.pop();
    }
    return connectedLands.size();
}

void Land::ChangeOwner(Player *newOwner)
{                                            //when attack successfully, the owner is another player.
    if(NULL != owner)
        owner->DeleteLand(this);
    owner = newOwner;
    owner->AddLand(this);
    color = owner->getColor();
    setColor(color);
}

void Land::AddGrid(Grid *newGrid){
    grids.insert(newGrid);
}

void Land::setColor(QColor color){
    for(set<Grid*>::iterator it=grids.begin();it!=grids.end();it++){
        (*it)->setColor(color);
    }
}
void Land::setDice(int diceSum){  //distribute dices to grids in a land.
    int sum=0,tmp,no,f[ROW*COLUMN];
    diceAmount=diceSum;
    for(set<Grid*>::iterator it=grids.begin();it!=grids.end();it++){
        (*it)->setDice(0);
        f[sum++]=0;
    }
    tmp=diceSum;
    no=0;
    while(tmp){
        if(f[no]==0){
            f[no]=1;
            tmp--;
        }
        no=(no+rand())%sum;
    }
    no=0;
    for(set<Grid*>::iterator it=grids.begin();it!=grids.end();it++,no++)
        if (f[no]==1)
            (*it)->setDice(1);
}

void Land::Enter(){
    setColor(color.lighter(80));
}

void Land::Exit(){
    setColor(color);
}
