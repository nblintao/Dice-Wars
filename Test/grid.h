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
    void setLand(Land *newLand);
    void setDice(int is);
    Land* getLand();

signals:
    void sendColorChange(void);
public slots:
private:
    QColor color;
    Land *homeLand;
    int dice;
};

#endif // GRID_H
