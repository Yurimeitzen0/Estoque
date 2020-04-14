#include "fm_main.h"
#include "ui_fm_main.h"
#include "fm_login.h"
#include "fm_venda.h"
#include "fm_gestoque.h"
#include "fm_gvendas.h"
#include "fm_gcolab.h"
#include "Global_variables.h"

int global_variables::id_colab;
QString global_variables::nome_colab;
QString global_variables::user_colab;
QString global_variables::acesso_colab;
bool global_variables::logged;

Fm_main::Fm_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fm_main)
{
    ui->setupUi(this);
    global_variables::logged = false;
    keylock_open.addFile(":/Imagens/imgs/cadeado_aberto.png");
    keylock_locked->addFile(":/Imagens/imgs/cadeado_fechado.png");
    ui->Bt_block->setIcon(*keylock_locked);
    ui->statusbar->setSizeGripEnabled(false);
    ui->statusbar->addPermanentWidget(ui->Bt_block, 0);
    //ui->statusbar->addWidget(ui->Bt_block);
    //ui->statusbar->addWidget(ui->label);




}

Fm_main::~Fm_main()
{
    delete ui;
}


void Fm_main::on_Bt_block_clicked()
{
    if (global_variables::logged)
    {
        global_variables::logged = false;
        ui->Bt_block->setIcon(*keylock_locked);
        ui->statusbar->showMessage("Controle bloqueado");

    }
    else
    {
        Fm_Login log_form;
        log_form.exec();

        if(global_variables::logged == true)
        {
            ui->Bt_block->setIcon(keylock_open);
            ui->statusbar->showMessage("Usuário: "+global_variables::nome_colab+" em uso");
            log_form.close();
        }
        else
            ui->statusbar->showMessage("Login cancelado");

    }

}

void Fm_main::on_Bt_Sale_clicked()
{
    Fm_venda form_sale;

    if(global_variables::logged)
    {
        form_sale.exec();
    }
    else
    {
        ui->statusbar->showMessage("Controle bloqueado, por favor faça login com um usuário valido");
    }

}

void Fm_main::on_actionEstoque_triggered()
{
    Fm_Gestoque form_gstock;
    if(global_variables::logged == true)
    {
        if(global_variables::acesso_colab == "A" )
        {
            form_gstock.exec();
        }
        else
            ui->statusbar->showMessage("Acesso não permitido.");

    }
    else
        ui->statusbar->showMessage("Nenhum usuário logado.");
}

void Fm_main::on_actionColaboradores_triggered()
{
    Fm_Gcolab form_gcolab;
    if(global_variables::logged == true)
    {
        if(global_variables::acesso_colab == "A" )
        {
            form_gcolab.exec();
        }
        else
            ui->statusbar->showMessage("Acesso não permitido.");

    }
    else
        ui->statusbar->showMessage("Nenhum usuário logado.");
}

void Fm_main::on_actionVendas_triggered()
{
    Fm_Gvendas form_gsale;
    if(global_variables::logged == true)
    {
        if(global_variables::acesso_colab == "A" )
        {
            form_gsale.exec();
        }
        else
            ui->statusbar->showMessage("Acesso não permitido.");

    }
    else
        ui->statusbar->showMessage("Nenhum usuário logado.");
}
