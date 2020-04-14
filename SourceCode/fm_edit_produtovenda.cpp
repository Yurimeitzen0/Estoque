#include "fm_edit_produtovenda.h"
#include "ui_fm_edit_produtovenda.h"

Fm_Edit_Produtovenda::Fm_Edit_Produtovenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fm_Edit_Produtovenda)
{
    ui->setupUi(this);
    ui->Txt_Eprod->setText(Fm_venda::v_prod);
    ui->Txt_Euni->setText(Fm_venda::v_uni);
    ui->Txt_Eqty->setText(Fm_venda::v_qty);
}

Fm_Edit_Produtovenda::~Fm_Edit_Produtovenda()
{
    delete ui;
}

void Fm_Edit_Produtovenda::on_Bt_edit_clicked()
{
    Fm_venda::v_uni = ui->Txt_Euni->text();
    std::replace(Fm_venda::v_uni.begin(),Fm_venda::v_uni.end(), ',' , '.');
    Fm_venda::v_qty = ui->Txt_Eqty->text();
    Fm_venda::edited = true;
    close();
}

void Fm_Edit_Produtovenda::on_Bt_cancel_clicked()
{
    Fm_venda::edited = false;
    close();
}
