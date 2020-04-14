#ifndef FM_EDIT_PRODUTOVENDA_H
#define FM_EDIT_PRODUTOVENDA_H

#include <QDialog>
#include "fm_venda.h"

namespace Ui {
class Fm_Edit_Produtovenda;
}

class Fm_Edit_Produtovenda : public QDialog
{
    Q_OBJECT

public:
    explicit Fm_Edit_Produtovenda(QWidget *parent = nullptr);
    ~Fm_Edit_Produtovenda();

private slots:
    void on_Bt_edit_clicked();

    void on_Bt_cancel_clicked();

private:
    Ui::Fm_Edit_Produtovenda *ui;
};

#endif // FM_EDIT_PRODUTOVENDA_H
