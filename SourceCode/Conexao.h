#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>
class Conexao
{
public:
    QSqlDatabase LoginDB;
    QString Local_Path{}, DB_Path{};
    Conexao()
    {
        LoginDB = QSqlDatabase::addDatabase("QSQLITE");
    }

    void close()
    {
        LoginDB.close();
    }
    bool open()
    {

        Local_Path = qApp->applicationDirPath();
        DB_Path = Local_Path + "/db/Control_Estoque.db";
        LoginDB.setDatabaseName(DB_Path);

        if(!LoginDB.open())
        {
           return false;
        }
        else
        {
            return true;
        }
    }
    bool isOpen()
    {
        return LoginDB.open()? true: false;
    }
};

#endif // CONEXAO_H

