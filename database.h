#ifndef DATABASE_H
#define DATABASE_H

#include<iostream>
#include<QtSql>
#include<QDebug>

class database
{
public:
    QSqlDatabase myDatabase;
    static database * getInstance();
    void SetDBPath(const QString &path);
    ~database();

private:
    database(){} //Private constructor, not to be used
    static bool isCreated; //Flag checking if the connection has been made
    static database * instance;//The instance will be stored here

};

#endif // DATABASE_H
