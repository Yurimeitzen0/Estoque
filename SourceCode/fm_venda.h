#ifndef FM_VENDA_H
#define FM_VENDA_H

#include <QDialog>
#include <QStatusBar>
#include "Conexao.h"
#include <QtSql>
#include <QTableWidget>

namespace Ui {
class Fm_venda;
}

class Fm_venda : public QDialog
{
    Q_OBJECT

public:
    explicit Fm_venda(QWidget *parent = nullptr);
    ~Fm_venda();
    QStatusBar * bar{nullptr};
    Conexao con;
    int countlines{0};
    double Total_venda{0};

    static QString v_prod_id, v_prod, v_qty, v_total, v_uni;
    static bool edited;

    void Clear_Form();

private slots:
    void on_Txt_Vcod_returnPressed();

    void on_Bt_Vdelete_clicked();

    void on_Bt_Veditp_clicked();

    void on_Bt_Vend_clicked();

private:
    Ui::Fm_venda *ui;
};

#endif // FM_VENDA_H
