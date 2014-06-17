#include "Land.h"


Land::Land()
{
    color = QColor(Qt::grey);
}


Land::~Land()
{
}

//bool Land::IsAdjacent(Land& anotherLand)
//{
//    return adjacentLands.count(anotherLand);
//}

//void Land::Attack(Land& attacked)
//{
//    int attackerDots, attackedDots;
//    int dots;
//    attackerDots = 0;
//    attackedDots = 0;

//    std::cout << "attacker: " << endl;
//    for (int i = 0; i < this->diceAmount; i++) {
//        dots = rand() % 6 + 1;
//        std::cout << dots << endl;
//        attackerDots += dots;
//    }
//    std::cout << "=" << attackerDots << endl;

//    std::cout << "attacked: " << endl;
//    for (int i = 0; i < attacked.diceAmount; i++) {
//        dots = rand() % 6 + 1;
//        std::cout << dots << endl;
//        attackerDots += dots;
//    }
//    std::cout << "=" << attackedDots << endl;
//    /*攻击成功*/
//    if (attackerDots>attackedDots) {
//        attacked.ChangeOwner(this->owner);
//        attacked.diceAmount = this->diceAmount - 1;
//        this->diceAmount = 1;
//    }
//    /*攻击失败*/
//    else {
//        this->diceAmount = 1;
//    }
//}

//void Land::ChangeOwner(Player& newOwner)
//{
//    (this->owner).DeleteLand(*this);
//    this->owner = newOwner;
//    newOwner.AddLand(*this);
//}

void Land::AddGrid(Grid& newGrid){
    grids.insert(newGrid);
}

void Land::setColor(QColor color){
    for(set<Grid&>::iterator it=grids.begin();it!=grids.end();it++){
        it->setColor(color);
    }
}
