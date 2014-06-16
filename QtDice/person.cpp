// person.cpp
#include "person.h"
//---------------------------------
//
Person::Person(QObject *parent) :
    QObject(parent), m_Name("unknow"), m_Age(0)
{
}
//---------------------------------
//
QString Person::getName(void) const
{
    return m_Name;
}
//---------------------------------
//
void Person::setName(const QString& name)
{
    m_Name = name;
    emit sendNameChange();
}
//---------------------------------
//
int Person::getAge(void)
{
    return m_Age;
}
//---------------------------------
//
void Person::setAge(int age)
{
    m_Age = age;
    emit sendAgeChange();
}
//---------------------------------
//
QColor Person::getColor(void) const
{
    return QColor(Qt::blue);
}
//---------------------------------
//
void Person::changeNameAndAge(void)
{
    setName("Luly");
    setAge(31);
}
