// person.h
#ifndef PERSON_H
#define PERSON_H
#include <QObject>
//#include <QDeclarativeListProperty>
#include <QList>
#include <QColor>
class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY sendNameChange)
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY sendAgeChange)
public:
    explicit Person(QObject *parent = 0);
    QString getName(void) const;
    void setName(const QString& name);
    int getAge(void);
    void setAge(int age);
    // 一个简单的函数, 获取蓝色
    Q_INVOKABLE QColor getColor(void) const;
    Q_INVOKABLE void changeNameAndAge(void);
signals:
    void sendNameChange(void);
    void sendAgeChange(void);
private:
    QString     m_Name;
    int         m_Age;
};
#endif // PERSON_H
