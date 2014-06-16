#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QList>
#include <QColor>
class Land;
class Grid : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY sendColorChange)
public:
    explicit Grid(QObject *parent = 0);
    Q_INVOKABLE QColor getColor(void) const;
    Q_INVOKABLE void setColor(QColor sColor);
    void setLand(Land& newLand);
    Land& getLand();

signals:
    void sendColorChange(void);
public slots:
private:
    QColor color;
    Land& homeLand;
};

#endif // GRID_H
