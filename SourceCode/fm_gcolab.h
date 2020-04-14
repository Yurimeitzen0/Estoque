#ifndef FM_GCOLAB_H
#define FM_GCOLAB_H

#include <QDialog>
#include <QStatusBar>
#include "Conexao.h"
#include <QTableWidget>

namespace Ui {
class Fm_Gcolab;
}

class Fm_Gcolab : public QDialog
{
    Q_OBJECT

public:
    explicit Fm_Gcolab(QWidget *parent = nullptr);
    ~Fm_Gcolab();
    Conexao con;

    QStatusBar * bar{nullptr};

    void Clear_Form();

    void Update_TableView(QString querystring = "select colab_id, colab_nome from tb_colaboradores order by colab_id");

    void Clear_GColab();

private slots:
    void on_Bt_Cnew_clicked();

    void on_Bt_Csave_clicked();

    void on_BT_Ccancel_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_TableView_itemSelectionChanged();

    void on_Bt_GCedit_clicked();

    void on_Bt_GCexcluir_clicked();

    void on_Bt_GCvendas_clicked();

    void on_Bt_GCfiltrar_clicked();

private:
    Ui::Fm_Gcolab *ui;
};

#endif // FM_GCOLAB_H
