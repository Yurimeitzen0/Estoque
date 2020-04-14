#include "fm_venda.h"
#include "ui_fm_venda.h"
#include <QMessageBox>
#include "fm_edit_produtovenda.h"
#include "fm_main.h"
#include "Global_variables.h"
#include "global_functions.h"

QString Fm_venda::v_prod_id;
QString Fm_venda::v_prod;
QString Fm_venda::v_uni;
QString Fm_venda::v_qty;
QString Fm_venda::v_total;
bool Fm_venda::edited;


Fm_venda::Fm_venda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fm_venda)
{
    ui->setupUi(this);
    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);

    ui->verticalLayout_4->addWidget(bar);
    ui->Txt_Vcod->setFocus();
    ui->TableView->setColumnCount(5);
    QStringList header{"Código", "Produto", "Valor Un.", "Qtd", "Total"};

    ui->TableView->setHorizontalHeaderLabels(header);
    QString Style{"QTableView {selection-background-color:purple}"};

    ui->TableView->setStyleSheet(Style);
    ui->TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView->verticalHeader()->setVisible(false);

    ui->TableView->setColumnWidth(0,150);
    ui->TableView->setColumnWidth(1,230);
    ui->TableView->setColumnWidth(2,80);
    ui->TableView->setColumnWidth(3,80);
    ui->TableView->setColumnWidth(4,80);

}

Fm_venda::~Fm_venda()
{
    delete ui;
}

void Fm_venda::Clear_Form()
{
    ui->Txt_Vcod->clear();
    ui->Txt_Vqty->setText("1");
}

void Fm_venda::on_Txt_Vcod_returnPressed()
{
    if(ui->Txt_Vcod->text() == "")
        bar->showMessage("Erro, primeiramente digite um código");
    else
    {
        QSqlQuery query;
        QString id = ui->Txt_Vcod->text();
        double Total_prod;
        QString querystring{"select produto_id, produto_nome, produto_venda produto from tb_produtos where produto_id = '"+id+"'"};
        if(con.open())
        {
            query.prepare(querystring);
            if(query.exec())
            {
                query.first();
                if(query.value(0).toString()!="")
                {
                    ui->TableView->insertRow(countlines);
                    Total_prod = ui->Txt_Vqty->text().toDouble() * query.value(2).toDouble();
                    Total_venda +=Total_prod;
                    for (int i = 0;i<5;i++)
                    {
                        if(i==3)
                            ui->TableView->setItem(countlines,i, new QTableWidgetItem(ui->Txt_Vqty->text()));
                        else if(i ==4)
                            ui->TableView->setItem(countlines,i, new QTableWidgetItem(QString::number(Total_prod)));
                        else
                           ui->TableView->setItem(countlines,i, new QTableWidgetItem(query.value(i).toString()));
                        ui->TableView->setRowHeight(countlines,20);
                    }

                    countlines++;
                    ui->L_Total->setText("R$"+QString::number(Total_venda)+"");
                    bar->showMessage("Item adicionado com sucesso");
                }
                else
                {
                    bar->showMessage("Nenhum produto referente ao código: "+ui->Txt_Vcod->text()+"");
                }
            }
            else
            {
                bar->showMessage("Erro ao inserir novo produto");
            }
        }
        else
        {
            bar->showMessage("Erro ao conectar com o banco de dados");
        }
    }

    if(con.isOpen())
        con.close();
    Clear_Form();

}

void Fm_venda::on_Bt_Vdelete_clicked()
{
    if(ui->TableView->currentRow()!=-1)
    {
        QMessageBox::StandardButton answer = QMessageBox::question(this,"Remover?","Confirma a remoção do produto?", QMessageBox::Yes | QMessageBox::No);
        if (answer == QMessageBox::Yes)
        {
            Total_venda -= ui->TableView->item(ui->TableView->currentRow(),4)->text().toDouble();
            ui->L_Total->setText("R$"+QString::number(Total_venda)+"");
            ui->TableView->removeRow(ui->TableView->currentRow());
            countlines--;
            bar->showMessage("Item removido com sucesso");
        }
        else
        {
            bar->showMessage("Remoção cancelada");
        }
    }
    else
    {
        bar->showMessage("Erro, Nenhum elemento selecionado");
    }
}


void Fm_venda::on_Bt_Veditp_clicked()
{
    if(ui->TableView->currentRow()!=-1)
    {
        int edit_row = ui->TableView->currentRow();

        v_prod_id = ui->TableView->item(edit_row,0)->text();
        v_prod = ui->TableView->item(edit_row,1)->text();
        v_uni = ui->TableView->item(edit_row,2)->text();
        v_qty = ui->TableView->item(edit_row,3)->text();
        v_total = ui->TableView->item(edit_row,4)->text();

        Fm_Edit_Produtovenda form_edit;
        form_edit.exec();


        if(edited)
        {
            bar->showMessage("Item selecionado foi alterado");
            ui->TableView->item(edit_row,2)->setText(v_uni);
            ui->TableView->item(edit_row,3)->setText(v_qty);
            double total_edit = v_uni.toDouble() * v_qty.toDouble();
            ui->TableView->item(edit_row,4)->setText(QString::number(total_edit));

            Total_venda-=v_total.toDouble();
            Total_venda+= total_edit;
            ui->L_Total->setText("R$"+QString::number(Total_venda)+"");
        }
        else
        {
            bar->showMessage("Alteração cancelada");
        }
    }


}

void Fm_venda::on_Bt_Vend_clicked()
{
    if(ui->TableView->rowCount()>0)
    {
        QString vendaMessage{""};
        int idVenda{};
        QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd");
        if(con.open())
        {
            QSqlQuery query;
            QString querystring{"insert into tb_vendas (venda_data, id_colab, venda_total, id_pagamento) values"
                                "('"+date+"',"+QString::number(global_variables::id_colab)+","+QString::number(Total_venda)+", 1)"};
            query.prepare(querystring);
            if(query.exec())
            {
                bar->showMessage("Venda Finalizada");
                querystring = "select venda_id from tb_vendas order by venda_id desc limit 1";
                query.prepare(querystring);
                if(query.exec())
                {
                    query.first();
                    idVenda = query.value(0).toInt();
                    vendaMessage = "ID Venda:"+QString::number(idVenda)+", Valor total: R$"+QString::number(Total_venda)+", inserida com sucesso";
                    int totalLinhas = ui->TableView->rowCount();
                    int prod_row = 0;
                    while (prod_row<totalLinhas)
                    {
                        QString prod = ui->TableView->item(prod_row,1)->text();
                        QString uni = ui->TableView->item(prod_row,2)->text();
                        //std::replace(uni.begin(),uni.end(), ',', '.');
                        QString qty = ui->TableView->item(prod_row,3)->text();
                        QString tot = ui->TableView->item(prod_row,4)->text();
                        //std::replace(tot.begin(),tot.end(), ',', '.');
                        querystring = "insert into tb_produtos_vendas (venda_id, movimentacao_produto, movimentacao_qty, valor_un, valor_total) values"
                                      "("+QString::number(idVenda)+",'"+prod+"',"+QString::number(qty.toInt())+","+QString::number(uni.toDouble())+","+QString::number(tot.toDouble())+")";

                        query.prepare(querystring);
                        if(query.exec())
                        {
                            bar->showMessage("Registro inserido com sucesso");

                        }
                        else
                        {
                            bar->showMessage("Erro ao inserir Registro");
                        }
                        prod_row++;
                    }

                    Global_functions::Clean_TableView(ui->TableView);
                    Clear_Form();
                    bar->showMessage(vendaMessage);
                }
                else
                {
                    bar->showMessage("Erro ao recuperar id da venda inserida");
                }

            }
            else
            {
                bar->showMessage("Erro ao inserir venda no banco de dados");
            }

        }
        else
        {
            bar->showMessage("Erro ao se conectar com o banco de dados");
        }
    }
    else
    {
        bar->showMessage("Erro, não existem produtos nesta venda");
    }
    if(con.isOpen())
        con.close();
    countlines=0;

}
