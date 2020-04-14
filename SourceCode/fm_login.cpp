#include "fm_login.h"
#include "ui_fm_login.h"
#include "fm_main.h"
#include "Global_variables.h"

Fm_Login::Fm_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fm_Login)
{
    ui->setupUi(this);
    bar = new QStatusBar(this);
    bar->setSizeGripEnabled(false);
    bar->setFixedHeight(16);
    ui->verticalLayout_2->addWidget(bar);
    ui->Txt_Name->setText("yuri");
    ui->Txt_Password->setText("123");


    logged = false;

}

Fm_Login::~Fm_Login()
{
    delete ui;
}


void Fm_Login::on_Bt_Login_clicked()
{
    if(!con.open())
        bar->showMessage("Erro ao conectar ao banco de dados");
    else
    {
        QString username, password;
        username = ui->Txt_Name->text();
        password = ui->Txt_Password->text();
        QSqlQuery query;
        query.prepare("select * from tb_colaboradores where colab_user = '"+username+"' and colab_senha = '"+password+"'");
        if(query.exec())
        {
            query.first();
            if (query.value(1).toString() !="")
            {
                global_variables::logged = true;
                global_variables::nome_colab = query.value(1).toString();
                global_variables::acesso_colab = query.value(5).toString();
                global_variables::id_colab = query.value(0).toInt();

                con.close();
                bar->showMessage("Login efetuado com sucesso");
                close();
            }
            else
            {
                logged = false;
                bar->showMessage("Usuário não encontrado");
                ui->Txt_Name->clear();
                ui->Txt_Password->clear();
            }

        }
        else
        {
            logged = false;
            bar->showMessage("Erro na pesquisa ao banco");
            ui->Txt_Name->clear();
            ui->Txt_Password->clear();
        }

    }

    con.close();

}

void Fm_Login::on_Bt_Cancel_clicked()
{
    global_variables::logged = false;
    close();
}
