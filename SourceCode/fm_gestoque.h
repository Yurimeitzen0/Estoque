#ifndef FM_GESTOQUE_H
#define FM_GESTOQUE_H
#include "Conexao.h"
#include <QStatusBar>
#include <QTableWidget>

#include <QDialog>

namespace Ui {
class Fm_Gestoque;
}

class Fm_Gestoque : public QDialog
{
    Q_OBJECT

public:
    explicit Fm_Gestoque(QWidget *parent = nullptr);
    ~Fm_Gestoque();
    void Clean_TableView(QTableWidget *);
    Conexao con;
    QStatusBar *bar{nullptr};

    void Update_TableView(QString querystring = "select produto_id, produto_nome from tb_produtos order by produto_id");

    void Clear_Gestoque();

private slots:
    void on_Bt_add_clicked();

    void on_Bt_save_clicked();

    void on_tabWidget_currentChanged(int index);


    void on_TableView_itemSelectionChanged();

    void on_Bt_Ggravar_clicked();

    void on_Bt_Gexcluir_clicked();

    void on_Bt_Gfiltrar_clicked();

private:
    Ui::Fm_Gestoque *ui;
};

#endif // FM_GESTOQUE_H
