#ifndef _GRID_H
#define _GRID_H

#include <QObject>
#include <QList>
#include <QColor>

class Land;

class Grid : public QObject
{
    Q_OBJECT
public:
    explicit Grid(QObject *parent = 0);
    Q_INVOKABLE QColor getColor(void) const;
    Q_INVOKABLE void setColor(QColor sColor);
    Q_INVOKABLE int getDice() const;
    void setLand(Land *newLand);  //使该格子属于一块领地
    void setDice(int amount);  //决定是否在这个方格中显示一颗骰子
    Land* getLand() const;    //用于访问私有变量land
signals:
    void sendColorChange(void);
public slots:
private:
    QColor color;
    Land *homeLand;
    int dice;
};

inline QColor Grid::getColor(void) const{
    return color;
}

inline void Grid::setColor(QColor sColor){
    this->color = sColor;
}

inline void Grid::setLand(Land *newLand){
    homeLand = newLand;
}

inline void Grid::setDice(int amount){
    dice=amount;
}

inline int Grid::getDice() const{
    return dice;
}

inline Land* Grid::getLand() const{
    return homeLand;
}

#endif // GRID_H
