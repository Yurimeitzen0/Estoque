#include "fm_gestoque.h"
#include "ui_fm_gestoque.h"
#include <QMessageBox>
#include <global_functions.h>

Fm_Gestoque::Fm_Gestoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fm_Gestoque)
{
    ui->setupUi(this);

    bar = new QStatusBar(this);
    ui->verticalLayout_10->addWidget(bar);
    bar->setSizeGripEnabled(false);
    bar->setFixedHeight(16);

    //Update_TableView();
    ui->TableView->setColumnCount(2);
    ui->tabWidget->setCurrentIndex(0);

    QStringList header{"Código", "Produto"};
    ui->TableView->setHorizontalHeaderLabels(header);
    QString Style{"QTableView {selection-background-color:purple}"};
    ui->TableView->setStyleSheet(Style);
    ui->TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView->verticalHeader()->setVisible(false);
    ui->TableView->setColumnWidth(0,80);
    ui->TableView->setColumnWidth(1,185);

}

Fm_Gestoque::~Fm_Gestoque()
{
    delete ui;
    if(con.isOpen())
        con.close();
}



void Fm_Gestoque::on_Bt_add_clicked()
{
    ui->Txt_cod->clear();
    ui->Txt_desc->clear();
    ui->Txt_venda->clear();
    ui->Txt_compra->clear();
    ui->Txt_estoque->clear();
    ui->Txt_fornecedor->clear();
    ui->Txt_cod->setFocus();

}

void Fm_Gestoque::on_Bt_save_clicked()
{
    if(con.open())
    {
        QString cod = ui->Txt_cod->text();
        QString desc = ui->Txt_desc->text();
        QString venda = ui->Txt_venda->text();
        std::replace(venda.begin(),venda.end(),',','.');
        QString compra = ui->Txt_compra->text();
        std::replace(compra.begin(),compra.end(), ',' , '.');
        QString stock = ui->Txt_estoque->text();
        QString fornecedor = ui->Txt_fornecedor->text();

        QSqlQuery query;

        QString querystring{"insert into tb_produtos (produto_id, produto_nome, fornecedor_id, produto_qty, produto_compra, produto_venda) "
                            "values ("+QString::number(cod.toInt())+", '"+desc+"', "+QString::number(fornecedor.toInt())+", "+QString::number(stock.toInt())+", "+QString::number(compra.toFloat())+", "+QString::number(venda.toFloat())+")"};
        query.prepare(querystring);
        if(query.exec())
        {
            bar->showMessage("Produto inserido com sucesso");
            ui->Txt_cod->clear();
            ui->Txt_desc->clear();
            ui->Txt_venda->clear();
            ui->Txt_compra->clear();
            ui->Txt_estoque->clear();
            ui->Txt_fornecedor->clear();
            ui->Txt_cod->setFocus();
        }
        else
        {
            bar->showMessage("Erro na query de inserção");
        }
        con.close();
    }
    else
    {
        bar->showMessage("Erro ao abrir banco de dados");
    }

}

void Fm_Gestoque::Update_TableView(QString querystring)
{
    if (con.open())
    {
       int countRows {0};
       //bar->showMessage("Conectado ao banco de dados");

       QSqlQuery query;
       query.prepare(querystring);
       if(query.exec())
       {
           while (query.next())
           {
               ui->TableView->insertRow(countRows);
               ui->TableView->setItem(countRows,0, new QTableWidgetItem(query.value(0).toString()));
               ui->TableView->setItem(countRows,1, new QTableWidgetItem(query.value(1).toString()));
               ui->TableView->setRowHeight(countRows,20);
               countRows++;
           }
       }
       else
       {
           bar->showMessage("Erro ao listar produtos.");
       }

    }
    else
    {
        bar->showMessage("Erro ao se conectar com o banco");
    }
    con.close();
}



void Fm_Gestoque::on_tabWidget_currentChanged(int index)
{
    bar->clearMessage();
     if (index == 0)
     {

         if(con.isOpen())
             con.close();
     }
     else if (index == 1)
     {
         Clear_Gestoque();
         Global_functions::Clean_TableView(ui->TableView);
         Update_TableView();

     }

}

void Fm_Gestoque::on_TableView_itemSelectionChanged()
{
    if(ui->TableView->currentRow()!=-1)
    {
        if(con.open())
        {
            int id = ui->TableView->item(ui->TableView->currentRow(),0)->text().toInt();
            QSqlQuery query;
            QString querytext{"select * from tb_produtos where produto_id = "+QString::number(id)+""};

            query.prepare(querytext);
            if(query.exec())
            {
                query.first();
                ui->Txt_Gcod->setText(query.value(0).toString());
                ui->Txt_Gdesc->setText(query.value(1).toString());
                ui->Txt_Gfornecedor->setText(query.value(2).toString());
                ui->Txt_Gestoque->setText(query.value(3).toString());
                ui->Txt_Gcompra->setText(query.value(4).toString());
                ui->Txt_Gvenda->setText(query.value(5).toString());

            }
            else
            {
                bar->showMessage("Erro ao retornar valor selecionado");
            }
        }
        else
        {
            bar->showMessage("Erro ao conectar com o banco de dados");
        }
        con.close();
    }

}

void Fm_Gestoque::on_Bt_Ggravar_clicked()
{
    if(ui->Txt_Gcod->text()=="")
    {
        bar->showMessage("Erro, primeiro selecione um registro");
    }
    else
    {
        if(con.open())
        {
            int id = ui->TableView->item(ui->TableView->currentRow(),0)->text().toInt();
            int line = ui->TableView->currentRow();
            QString prod = ui->Txt_Gdesc->text();
            QString venda = ui->Txt_Gvenda->text();
            std::replace(venda.begin(),venda.end(),',','.');
            QString compra = ui->Txt_Gcompra->text();
            std::replace(compra.begin(),compra.end(),',','.');
            QString forn = ui->Txt_Gfornecedor->text();
            QString qty = ui->Txt_Gestoque->text();




            QSqlQuery query;
            QString querytext{"update tb_produtos set "
                              "produto_id ="+QString::number(id)+", produto_nome = '"+prod+"', fornecedor_id = "+QString::number(forn.toInt())+", produto_qty = "+QString::number(qty.toInt())+", produto_compra = "+QString::number(compra.toFloat())+", produto_venda = "+QString::number(venda.toFloat())+" where produto_id = "+QString::number(id)+""};
            query.prepare(querytext);
            if (query.exec())
            {
                con.close();
                Global_functions::Clean_TableView(ui->TableView);
                Update_TableView();
                bar->showMessage("Valor atualizado com sucesso");
                ui->TableView->setCurrentCell(line,0);
            }
            else
                bar->showMessage("Erro ao atualizar dados");
        }
        else
        {
            bar->showMessage("Erro ao conectar com o banco de dados");
        }

    }
    if(con.isOpen())
        con.close();
}

void Fm_Gestoque::on_Bt_Gexcluir_clicked()
{
    if(ui->Txt_Gcod->text()=="")
    {
        bar->showMessage("Erro, primeiro selecione um registro");
    }
    else
    {
        QMessageBox::StandardButton answer =  QMessageBox::question(this, "Exclusão", "Confirma a remoção do produto selecionado?", QMessageBox::Yes | QMessageBox::No);

        if(answer == QMessageBox::Yes)
        {
            con.open();
            int remove_line = ui->TableView->item(ui->TableView->currentRow(),0)->text().toInt();
            QSqlQuery query;
            QString querystring{"delete from tb_produtos where produto_id = "+QString::number(remove_line)+""};
            query.prepare(querystring);
            if (query.exec())
            {
                con.close();
                Clear_Gestoque();
                Global_functions::Clean_TableView(ui->TableView);
                Update_TableView();
                //bar->showMessage("Produto removido com sucesso.");
            }
            else
            {
                bar->showMessage("Erro ao remover produto");
            }
            if(con.isOpen())
                con.close();
        }
        else
        {
            bar->showMessage("Exclusão cancelada");
        }
    }

}

void Fm_Gestoque::Clear_Gestoque()
{
    ui->TableView->setCurrentCell(-1,0);
    ui->TableView->clear();
    QStringList header{"Código", "Produto"};
    ui->TableView->setHorizontalHeaderLabels(header);
    QString Style{"QTableView {selection-background-color:purple}"};
    ui->TableView->setStyleSheet(Style);
    ui->TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView->verticalHeader()->setVisible(false);
    ui->TableView->setColumnWidth(0,80);
    ui->TableView->setColumnWidth(1,185);

    ui->Txt_Gcod->clear();
    ui->Txt_Gdesc->clear();
    ui->Txt_Gvenda->clear();
    ui->Txt_Gcompra->clear();
    ui->Txt_Gestoque->clear();
    ui->Txt_Gfornecedor->clear();
}

void Fm_Gestoque::on_Bt_Gfiltrar_clicked()
{
    QString querystring{""};

    if (ui->Txt_Gfiltrar->text() == "")
    {
        if(ui->Rb_Gcod->isChecked())
        {
            querystring = "select produto_id, produto_nome from tb_produtos order by produto_id";
        }
        else
        {
            querystring = "select produto_id, produto_nome from tb_produtos order by produto_nome";
        }
    }
    else
    {
        if(ui->Rb_Gcod->isChecked())
        {
            querystring = "select produto_id, produto_nome from tb_produtos where produto_id = "+QString::number(ui->Txt_Gfiltrar->text().toInt())+" order by produto_id";
        }
        else
        {
            querystring = "select produto_id, produto_nome from tb_produtos where produto_nome like '%"+ui->Txt_Gfiltrar->text()+"%' order by produto_id";
        }
    }


    bar->showMessage("Opções de filtro atualizadas");
    Clear_Gestoque();
    Global_functions::Clean_TableView(ui->TableView);
    Update_TableView(querystring);




}
