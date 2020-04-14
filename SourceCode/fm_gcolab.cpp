#include "fm_gcolab.h"
#include "ui_fm_gcolab.h"
#include "global_functions.h"
#include "QMessageBox"

Fm_Gcolab::Fm_Gcolab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fm_Gcolab)
{
    ui->setupUi(this);
    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    bar->setFixedHeight(16);
    ui->verticalLayout_8->addWidget(bar);

    ui->cb_Cacesso->addItem("A");
    ui->cb_Cacesso->addItem("B");
    ui->Txt_Cnome->setFocus();

    ui->TableView->setColumnCount(2);
    ui->tabWidget->setCurrentIndex(0);

    QStringList header{"ID", "Usuário"};
    ui->TableView->setHorizontalHeaderLabels(header);
    QString Style{"QTableView {selection-background-color:purple}"};
    ui->TableView->setStyleSheet(Style);
    ui->TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView->verticalHeader()->setVisible(false);
    ui->TableView->setColumnWidth(0,80);
    ui->TableView->setColumnWidth(1,135);


}

Fm_Gcolab::~Fm_Gcolab()
{
    delete ui;
}

void Fm_Gcolab::Clear_Form()
{
    ui->Txt_GCcod->clear();
    ui->Txt_Cnome->clear();
    ui->Txt_Cphone->clear();
    ui->Txt_Cusername->clear();
    ui->Txt_Cpassword->clear();
    ui->cb_Cacesso->setCurrentIndex(0);
    ui->Txt_GCfiltrar->clear();
    ui->Txt_Cnome->setFocus();
}

void Fm_Gcolab::on_Bt_Cnew_clicked()
{
    Clear_Form();

}

void Fm_Gcolab::on_Bt_Csave_clicked()
{
    if(con.open())
    {
        QString colab_nome = ui->Txt_Cnome->text();
        QString colab_user = ui->Txt_Cusername->text();
        QString colab_password = ui->Txt_Cpassword->text();
        QString colab_phone = ui->Txt_Cphone->text();
        QString colab_acesso = ui->cb_Cacesso->currentText();

        QSqlQuery query;

        QString querystring{"insert into tb_colaboradores (colab_nome, colab_user, colab_senha, colab_phone, acesso_colab) "
                            "values ('"+colab_nome+"','"+colab_user+"','"+colab_password+"','"+colab_phone+"','"+colab_acesso+"' )"};
        query.prepare(querystring);
        if(query.exec())
        {
            bar->showMessage("Colaborador inserido com sucesso.");
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
    Clear_Form();
}

void Fm_Gcolab::on_BT_Ccancel_clicked()
{
    close();
}



void Fm_Gcolab::Update_TableView(QString querystring)
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
           bar->showMessage("Erro ao listar colaboradores.");
       }

    }
    else
    {
        bar->showMessage("Erro ao se conectar com o banco.");
    }
    con.close();
}

void Fm_Gcolab::Clear_GColab()
{
    ui->TableView->setCurrentCell(-1,0);
    ui->TableView->clear();
    QStringList header{"ID", "Usuário"};
    ui->TableView->setHorizontalHeaderLabels(header);
    QString Style{"QTableView {selection-background-color:purple}"};
    ui->TableView->setStyleSheet(Style);
    ui->TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView->verticalHeader()->setVisible(false);
    ui->TableView->setColumnWidth(0,80);
    ui->TableView->setColumnWidth(1,135);

    Clear_Form();
}

void Fm_Gcolab::on_tabWidget_currentChanged(int index)
{
    bar->clearMessage();
     if (index == 0)
     {
         if(con.isOpen())
             con.close();
     }
     else if (index == 1)
     {
         Clear_GColab();
         Global_functions::Clean_TableView(ui->TableView);
         Update_TableView();
         //Update_TableView();

     }
}

void Fm_Gcolab::on_TableView_itemSelectionChanged()
{
    if(ui->TableView->currentRow()!=-1)
    {
        if(con.open())
        {
            int id = ui->TableView->item(ui->TableView->currentRow(),0)->text().toInt();
            QSqlQuery query;
            QString querytext{"select * from tb_colaboradores where colab_id = "+QString::number(id)+""};

            query.prepare(querytext);
            if(query.exec())
            {
                query.first();
                ui->Txt_GCcod->setText(query.value(0).toString());
                ui->Txt_GCnome->setText(query.value(1).toString());
                ui->Txt_GCusername->setText(query.value(2).toString());
                ui->Txt_GCpassword->setText(query.value(3).toString());
                ui->Txt_GCphone->setText(query.value(4).toString());
                ui->Txt_GCacesso->setText(query.value(5).toString());

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

void Fm_Gcolab::on_Bt_GCedit_clicked()
{
    if(ui->Txt_GCcod->text()=="")
    {
        bar->showMessage("Erro, primeiro selecione um registro");
    }
    else
    {
        if(con.open())
        {
            int id = ui->TableView->item(ui->TableView->currentRow(),0)->text().toInt();
            int line = ui->TableView->currentRow();
            QString nome = ui->Txt_GCnome->text();
            QString user = ui->Txt_GCusername->text();
            QString password = ui->Txt_GCpassword->text();
            QString phone = ui->Txt_GCphone->text();
            QString acesso = ui->Txt_GCacesso->text();




            QSqlQuery query;
            QString querytext{"update tb_colaboradores set "
                              "colab_nome = '"+nome+"', colab_user = '"+user+"', colab_senha = '"+password+"', colab_phone = '"+phone+"', colab_acesso = '"+acesso+"' where colab_id = '"+QString::number(id)+"'"};
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

void Fm_Gcolab::on_Bt_GCexcluir_clicked()
{
    if(ui->Txt_GCcod->text()=="")
    {
        bar->showMessage("Erro, primeiro selecione um registro");
    }
    else
    {
        QMessageBox::StandardButton answer =  QMessageBox::question(this, "Exclusão", "Confirma a remoção do usuário selecionado?", QMessageBox::Yes | QMessageBox::No);

        if(answer == QMessageBox::Yes)
        {
            con.open();
            int remove_line = ui->TableView->item(ui->TableView->currentRow(),0)->text().toInt();
            QSqlQuery query;
            QString querystring{"delete from tb_colaboradores where colab_id = "+QString::number(remove_line)+""};
            query.prepare(querystring);
            if (query.exec())
            {
                con.close();
                Clear_GColab();
                Global_functions::Clean_TableView(ui->TableView);
                Update_TableView();
                bar->showMessage("Usuário removido com sucesso.");
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

void Fm_Gcolab::on_Bt_GCvendas_clicked()
{

}

void Fm_Gcolab::on_Bt_GCfiltrar_clicked()
{
    QString querystring{""};

    if (ui->Txt_GCfiltrar->text() == "")
    {
        if(ui->Rb_GCcod->isChecked())
        {
            querystring = "select colab_id, colab_nome from tb_colaboradores order by colab_id";
        }
        else
        {
            querystring = "select colab_id, colab_nome from tb_colaboradores order by colab_nome";
        }
    }
    else
    {
        if(ui->Rb_GCcod->isChecked())
        {
            querystring = "select colab_id, colab_nome from tb_colaboradores where colab_id = "+ui->Txt_GCfiltrar->text()+" order by colab_id";
        }
        else
        {
            querystring = "select colab_id, colab_nome from tb_colaboradores where colab_nome like '%"+ui->Txt_GCfiltrar->text()+"%' order by colab_id";
        }
    }


    bar->showMessage("Opções de filtro atualizadas");
    Clear_GColab();
    ui->Txt_GCfiltrar->setFocus();
    Global_functions::Clean_TableView(ui->TableView);
    Update_TableView(querystring);


}
