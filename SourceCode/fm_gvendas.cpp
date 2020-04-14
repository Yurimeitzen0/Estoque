#include "fm_gvendas.h"
#include "ui_fm_gvendas.h"
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QDesktopServices>
#include <xlsxdocument.h>

#include <QPixmap>

Fm_Gvendas::Fm_Gvendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fm_Gvendas)
{
    ui->setupUi(this);

    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    bar->setFixedHeight(16);
    ui->verticalLayout_3->addWidget(bar);

    ui->TableView_vendas->setColumnCount(5);
    ui->TableView_vendas->horizontalHeader()->setVisible(true);
    QStringList header{"ID", "Data", "Colaborador", "V.Total", "T.Pagamento"};
    ui->TableView_vendas->setHorizontalHeaderLabels(header);
    QString Style{"QTableView {selection-background-color:purple}"};
    ui->TableView_vendas->setStyleSheet(Style);
    ui->TableView_vendas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView_vendas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView_vendas->verticalHeader()->setVisible(false);
    ui->TableView_vendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->TableView_vendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->TableView_produtos->setColumnCount(5);
    QStringList header2{"Mov", "Produto", "Qty", "V.Uni", "V.Total"};
    ui->TableView_produtos->setHorizontalHeaderLabels(header2);
    ui->TableView_produtos->setStyleSheet(Style);
    ui->TableView_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TableView_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->TableView_produtos->verticalHeader()->setVisible(false);
    ui->TableView_produtos->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->TableView_produtos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->Date_end->setDate(QDate::currentDate());


    int countlines{0};
    if(con.open())
    {
        QSqlQuery query;
        query.prepare("select * from tb_vendas");
        if(query.exec())
        {
            query.first();
            do
            {
                ui->TableView_vendas->insertRow(countlines);
                for (int i = 0; i<5;i++)
                    ui->TableView_vendas->setItem(countlines,i, new QTableWidgetItem(query.value(i).toString()));
                countlines++;
            }while (query.next());

        }
        else
        {
            bar->showMessage("Erro ao recuperar dados");
        }
    }
    else
    {
        bar->showMessage("Erro ao abrir banco de dados");
    }
    con.close();


}

Fm_Gvendas::~Fm_Gvendas()
{
    delete ui;
}

void Fm_Gvendas::on_TableView_vendas_itemSelectionChanged()
{
    if(ui->TableView_vendas->currentRow()!=-1)
    {
        QString venda_id = ui->TableView_vendas->item(ui->TableView_vendas->currentRow(),0)->text();
        ui->TableView_produtos->clear();
        ui->TableView_produtos->setRowCount(0);
        int countlines{0};

        if(con.open())
        {
            QSqlQuery query;
            query.prepare("select movimentacao_id, movimentacao_produto, movimentacao_qty, valor_un, valor_total from tb_produtos_vendas where venda_id ="+venda_id+"");
            if(query.exec())
            {
                query.first();
                if(query.value(0).toString()!="")
                {
                    do
                    {
                        ui->TableView_produtos->insertRow(countlines);
                        for (int i = 0; i<5;i++)
                            ui->TableView_produtos->setItem(countlines,i, new QTableWidgetItem(query.value(i).toString()));
                        countlines++;
                    }while (query.next());
                }
            }
            else
            {
                bar->showMessage(query.lastError().text());
            }
        }
        else
        {
            bar->showMessage("Erro ao abrir banco de dados");
        }
        con.close();
    }
}

void Fm_Gvendas::on_Bt_search_clicked()
{
    ui->TableView_vendas->setRowCount(0);
    ui->TableView_vendas->setCurrentCell(-1,0);
    ui->TableView_produtos->setRowCount(0);

    int countlines{0};
    if(con.open())
    {
        QSqlQuery query;
        query.prepare("select * from tb_vendas where venda_data between '"+ui->Date_begin->text()+"' and '"+ui->Date_end->text()+"'");
        if(query.exec())
        {
            query.first();
            if(query.value(0).toString()!="")
            {
                do
                {
                    ui->TableView_vendas->insertRow(countlines);
                    for (int i = 0; i<5;i++)
                        ui->TableView_vendas->setItem(countlines,i, new QTableWidgetItem(query.value(i).toString()));
                    countlines++;
                }while (query.next());
            }
        }
        else
        {
            bar->showMessage("Erro ao recuperar dados");
        }
    }
    else
    {
        bar->showMessage("Erro ao abrir banco de dados");
    }
    con.close();
}

void Fm_Gvendas::on_BT_show_clicked()
{
    ui->TableView_vendas->setRowCount(0);
    ui->TableView_vendas->setCurrentCell(-1,0);
    ui->TableView_produtos->setRowCount(0);

    int countlines{0};
    if(con.open())
    {
        QSqlQuery query;
        query.prepare("select * from tb_vendas");
        if(query.exec())
        {
            query.first();
            do
            {
                ui->TableView_vendas->insertRow(countlines);
                for (int i = 0; i<5;i++)
                    ui->TableView_vendas->setItem(countlines,i, new QTableWidgetItem(query.value(i).toString()));
                countlines++;
            }while (query.next());

        }
        else
        {
            bar->showMessage("Erro ao recuperar dados");
        }
    }
    else
    {
        bar->showMessage("Erro ao abrir banco de dados");
    }
    con.close();
}

void Fm_Gvendas::on_BT_pdf_clicked()
{
    QPrinter printer;
    QPainter painter;
    QString nome;
    if(ui->TableView_vendas->currentRow()!=-1)
    {
        nome = QDir::currentPath()+"/"+ui->TableView_vendas->item(ui->TableView_vendas->currentRow(),0)->text()+"_vendas.pdf";


        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(nome);


        if(painter.begin(&printer))
        {
            bar->showMessage("Arquivo PDF gerado com sucesso");
        }
        else
        {
            bar->showMessage("Erro ao gerar PDF");
            return;
        }
        int beginline = 500;
        int salto = 25;

        painter.drawPixmap(25,0,QPixmap(":/Imagens/imgs/source.png"));
        painter.drawText(25,beginline-50,"ID: "+ui->TableView_vendas->item(ui->TableView_vendas->currentRow(),0)->text());
        painter.drawText(150,beginline-50,"Data:"+ui->TableView_vendas->item(ui->TableView_vendas->currentRow(),1)->text());

        for (int i= 0; i <ui->TableView_produtos->rowCount();i++)
        {
            painter.drawText(25,beginline, ui->TableView_produtos->item(i,0)->text());
            painter.drawText(50,beginline, ui->TableView_produtos->item(i,1)->text());
            painter.drawText(300,beginline, ui->TableView_produtos->item(i,2)->text());

            beginline+=salto;
        }


        printer.newPage();

        painter.drawText(25,25,"Controle de Estoque");

        painter.end();
        QDesktopServices::openUrl(QUrl("file:///"+nome));
    }
    else
    {
        bar->showMessage("Primeiramente selecione um campo para gerar o PDF");
    }




}

void Fm_Gvendas::on_Bt_exel_clicked()
{
    QString nome;
    QXlsx::Document planilha;
    if(ui->TableView_vendas->currentRow()!=-1)
    {
        nome = QDir::currentPath()+"\\Venda"+ui->TableView_vendas->item(ui->TableView_vendas->currentRow(),0)->text()+"_planilha.xlsx";
        //planilha.write("A1",ui->TableView_produtos->item(0,0)->text());

        for (int i = 0;i <ui->TableView_produtos->rowCount();i++)
        {
            planilha.write("A"+QString::number(i+1),ui->TableView_produtos->item(i,0)->text());
            planilha.write("B"+QString::number(i+1),ui->TableView_produtos->item(i,1)->text());
            planilha.write("C"+QString::number(i+1),ui->TableView_produtos->item(i,2)->text());
        }
        planilha.saveAs(nome);
        bar->showMessage("Planilha Venda"+ui->TableView_vendas->item(ui->TableView_vendas->currentRow(),0)->text()+"_planilha.xlsx gerada com sucesso");
        //QDesktopServices::openUrl(QUrl("file:///"+nome));
    }
    else
    {
        bar->showMessage("Primeiramente selecione um campo para gerar a planilha");
    }
}

void Fm_Gvendas::on_teste_clicked()
{

    QString nome;
    int insertline{1};
    //QStringList titulos;

    QStringList colunas {"A","B","C","D","E"};
    nome = QDir::currentPath()+"\\inserir.xlsx";
    QXlsx::Document planilha(nome);



    int i = 0;
    for (int l = 0; l < 3; l++)
    {
        int countrows = ui->TableView_produtos->rowCount();
        ui->TableView_produtos->insertRow(countrows);
        for(QString item:colunas)
        {
            //titulos.append(planilha.read(item + QString::number(insertline)).toString());
            ui->TableView_produtos->setItem(countrows,i, new QTableWidgetItem(planilha.read(item + QString::number(insertline+l)).toString()));
            i++;
        }
        i = 0;


    }



}
