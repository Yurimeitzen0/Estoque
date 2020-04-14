#ifndef FM_GVENDAS_H
#define FM_GVENDAS_H

#include <QDialog>
#include <QStatusBar>
#include "Conexao.h"

namespace Ui {
class Fm_Gvendas;
}

class Fm_Gvendas : public QDialog
{
    Q_OBJECT

public:
    explicit Fm_Gvendas(QWidget *parent = nullptr);
    ~Fm_Gvendas();
    QStatusBar *bar{nullptr};
    Conexao con;


private slots:
    void on_TableView_vendas_itemSelectionChanged();

    void on_Bt_search_clicked();

    void on_BT_show_clicked();

    void on_BT_pdf_clicked();

    void on_Bt_exel_clicked();

    void on_teste_clicked();

private:
    Ui::Fm_Gvendas *ui;
};

#endif // FM_GVENDAS_H
