#ifndef FM_LOGIN_H
#define FM_LOGIN_H
#include "Conexao.h"
#include "QStatusBar"
#include <QDialog>
#include <QtSql>

namespace Ui {
class Fm_Login;
}

class Fm_Login : public QDialog
{
    Q_OBJECT

public:
    explicit Fm_Login(QWidget *parent = nullptr);
    ~Fm_Login();
    bool logged;
    Conexao con;
    QString nome, acesso;
    int id;

private slots:
    void on_Bt_Login_clicked();

    void on_Bt_Cancel_clicked();

private:
    Ui::Fm_Login *ui;
    QStatusBar *bar{nullptr};
};

#endif // FM_LOGIN_H
