#include "Land.h"


Land::Land()
{
    owner = NULL;
    color = QColor(Qt::yellow);
    diceAmount=0;
}


Land::~Land()
{
}

bool Land::IsAdjacent(Land *anotherLand)
{
    return adjacentLands.count(anotherLand);
}

void Land::Attack(Land *attacked)
{
    int attackerDots, attackedDots;
    int dots;
    attackerDots = 0;
    attackedDots = 0;

    std::cout << "attacker: " << endl;
    for (int i = 0; i < this->diceAmount; i++) {
        dots = rand() % 6 + 1;
        std::cout << dots << endl;
        attackerDots += dots;
    }
    std::cout << "=" << attackerDots << endl;

    std::cout << "attacked: " << endl;
    for (int i = 0; i < attacked->diceAmount; i++) {
        dots = rand() % 6 + 1;
        std::cout << dots << endl;
        attackerDots += dots;
    }
    std::cout << "=" << attackedDots << endl;
    /*攻击成功*/
    if (attackerDots>attackedDots) {
        attacked->ChangeOwner(this->owner);
        attacked->diceAmount = this->diceAmount - 1;
        this->diceAmount = 1;
    }
    /*攻击失败*/
    else {
        this->diceAmount = 1;
    }
}

void Land::ChangeOwner(Player *newOwner)
{
    if(NULL != owner)
        owner->DeleteLand(this);
    owner = newOwner;
    owner->AddLand(this);
    color = owner->getColor();
}

void Land::AddGrid(Grid *newGrid){
    grids.insert(newGrid);
}

void Land::setColor(QColor color){
    for(set<Grid*>::iterator it=grids.begin();it!=grids.end();it++){
        (*it)->setColor(color);
    }
}
void Land::setDice(int diceSum){
    int sum=0,tmp,no,f[200];
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
